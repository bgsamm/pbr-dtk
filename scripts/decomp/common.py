import logging


class AnalysisError(Exception):
    pass


def _make_log_message(msg: str, pc: int) -> str:
    return f"{msg} (pc=0x{pc:X})"


def log_debug(msg: str, pc: int) -> None:
    message = _make_log_message(msg, pc)
    logging.debug(message)


def log_info(msg: str, pc: int) -> None:
    message = _make_log_message(msg, pc)
    logging.info(message)


def log_warning(msg: str, pc: int) -> None:
    message = _make_log_message(msg, pc)
    logging.warning(message)


def log_error(msg: str, pc: int) -> None:
    message = _make_log_message(msg, pc)
    logging.error(message)


__all__ = ["AnalysisError", "log_debug", "log_info", "log_warning", "log_error"]
