from itertools import count
from rvl import Dol
from typealiases import *
from .event import VmCallback, VmEvent, VmHaltException
from .state import VmState
from .thread import VmCallback, VmThread
import logging


class WiiVm:
    _threads: list[VmThread]
    _callbacks: dict[type[VmEvent], VmCallback]

    # TODO Do I really want to be passing a DOL in?
    def __init__(self, dol: Dol):
        self._dol = dol
        self._threads = []
        self._callbacks = {}

    @property
    def thread_count(self) -> int:
        return len(self._threads)

    def register_callback[E: VmEvent](
        self, event: type[E], callback: VmCallback[E]
    ) -> VmCallback[E] | None:
        old_callback = self._callbacks.get(event)
        self._callbacks[event] = callback
        return old_callback

    def run(
        self,
        entry_point: int | None = None,
        init_state: VmState | None = None,
    ):
        self._threads.clear()

        start_state = init_state or VmState()
        start_thread = VmThread(self._dol, start_state, count(0), self._callbacks)

        assert start_thread.id == 0

        if entry_point:
            start_thread.pc = entry_point
        elif start_thread.pc.is_unknown:
            start_thread.pc = self._dol.entry_point

        self._threads.append(start_thread)

        logging.debug(f"VM started at entry point = 0x{entry_point:X}")

        while len(self._threads) > 0:
            thread = self._threads.pop()

            if thread.should_terminate:
                n_threads = len(self._threads)
                logging.debug(f"Thread finished; total threads remaining: {n_threads}")
                continue

            try:
                branches = thread.step()
                self._threads.extend(branches)
            except VmHaltException:
                thread.should_terminate = True

        logging.debug(f"VM finished running")
