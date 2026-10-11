# Usage: python3 tools/stubgen/tailcalls.py src/.unsorted/<ADDR> [--apply]
# Second pass of tools/stubgen/trivial.py: tail calls with arguments, constant stores, sda addresses.
import re,sys,subprocess,os
ROOT=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
unit=sys.argv[1]; apply="--apply" in sys.argv
tmp=os.path.join(os.environ.get("TMPDIR","/tmp"),"gen2_"+os.path.basename(unit)+".s")
subprocess.run([f"{ROOT}/build/tools/dtk","elf","disasm",f"{ROOT}/build/RPBP01/obj/{unit}.o",tmp],capture_output=True)
src=f"{ROOT}/{unit}.cpp"; existing=open(src).read() if os.path.exists(src) else ""
fns={};cur=None
for l in open(tmp):
    m=re.match(r"\.fn (\S+), ",l)
    if m: cur=m.group(1);fns[cur]=[];continue
    if l.startswith(".endfn"): cur=None;continue
    if cur:
        m=re.match(r"/\* [0-9A-F]+ [0-9A-F]+  [0-9A-F ]+ \*/\t(.*)",l)
        if m: fns[cur].append(m.group(1).strip())
        elif l.startswith(".L"): fns[cur].append("LABEL")
os.remove(tmp)
A="u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7"
def args(repl):
    a=[f"a{i}" for i in range(8)]
    for k,v in repl.items(): a[k]=v
    return ", ".join(a)
N=r"(-?0x[0-9a-f]+|-?\d+)"
T={"stw":"u32","sth":"u16","stb":"u8","lwz":"u32","lhz":"u16","lbz":"u8","lha":"s16"}
protos={}; vars_={}; code=[]
defined=set(re.findall(r"\b(fn_[0-9A-F]{8})\s*\(",existing))
gen_names=set()
def tail(f,tgt,repl):
    if tgt in defined or tgt in fns and not tgt.startswith("fn_"): return None
    if re.search(r"\b"+tgt+r"\b",existing): return None
    protos[tgt]=f"void {tgt}({A});"
    return f"void {f}({A}) {{ {tgt}({args(repl)}); }}"
def var(name,decl):
    if re.search(r"\b"+name+r"\b",existing): return False
    if name in vars_ and vars_[name]!=decl: return False
    vars_[name]=decl; return True
for f,ins in fns.items():
    if not re.fullmatch(r"fn_[0-9A-F]{8}",f) or re.search(r"\b"+f+r"\b",existing): continue
    b=None; s=" ; ".join(ins)
    m=re.fullmatch(rf"lwz r5, {N}\(r3\) ; b (fn_[0-9A-F]{{8}})",s)
    if m: b=tail(f,m.group(2),{2:f"*(u32 *)(a0 + {m.group(1)})"})
    m=re.fullmatch(rf"lwz r5, {N}\(r3\) ; li r6, {N} ; b (fn_[0-9A-F]{{8}})",s)
    if m: b=tail(f,m.group(3),{2:f"*(u32 *)(a0 + {m.group(1)})",3:m.group(2)})
    m=re.fullmatch(rf"lwz r3, {N}\(r3\) ; b (fn_[0-9A-F]{{8}})",s)
    if m: b=tail(f,m.group(2),{0:f"*(u32 *)(a0 + {m.group(1)})"})
    m=re.fullmatch(rf"addi r3, r3, {N} ; b (fn_[0-9A-F]{{8}})",s)
    if m: b=tail(f,m.group(2),{0:f"a0 + {m.group(1)}"})
    m=re.fullmatch(rf"subi r3, r3, {N} ; b (fn_[0-9A-F]{{8}})",s)
    if m: b=tail(f,m.group(2),{0:f"a0 - {m.group(1)}"})
    m=re.fullmatch(rf"mr r3, r4 ; b (fn_[0-9A-F]{{8}})",s)
    if m: b=tail(f,m.group(1),{0:"a1"})
    m=re.fullmatch(rf"li r4, {N} ; b (fn_[0-9A-F]{{8}})",s)
    if m: b=tail(f,m.group(2),{1:m.group(1)})
    m=re.fullmatch(rf"li r3, {N} ; b (fn_[0-9A-F]{{8}})",s)
    if m: b=tail(f,m.group(2),{0:m.group(1)})
    m=re.fullmatch(rf"lis r5, (lbl_\w+)@ha ; mr r4, r3 ; addi r3, r5, (lbl_\w+)@l ; b (fn_[0-9A-F]{{8}})",s)
    if m and m.group(1)==m.group(2) and var(m.group(1),f"extern u8 {m.group(1)}[];"): b=tail(f,m.group(3),{0:f"(u32){m.group(1)}",1:"a0"})
    m=re.fullmatch(rf"lis r3, (lbl_\w+)@ha ; addi r3, r3, (lbl_\w+)@l ; b (fn_[0-9A-F]{{8}})",s)
    if m and m.group(1)==m.group(2) and var(m.group(1),f"extern u8 {m.group(1)}[];"): b=tail(f,m.group(3),{0:f"(u32){m.group(1)}"})
    m=re.fullmatch(rf"li r0, {N} ; (stw|sth|stb) r0, {N}\(r3\) ; blr",s)
    if m: t=T[m.group(2)]; b=f"void {f}(u8 *p) {{ *({t} *)(p + {m.group(3)}) = {m.group(1)}; }}"
    m=re.fullmatch(rf"li r0, {N} ; (stw|sth|stb) r0, (lbl_\w+)@sda21\(r0\) ; blr",s)
    if m and var(m.group(3),f"extern {T[m.group(2)]} {m.group(3)};"): b=f"void {f}(void) {{ {m.group(3)} = {m.group(1)}; }}"
    m=re.fullmatch(rf"(stw|sth|stb) r4, {N}\(r3\) ; (stw|sth|stb) r5, {N}\(r3\) ; blr",s)
    if m: b=f"void {f}(u8 *p, {T[m.group(1)]} x, {T[m.group(3)]} y) {{ *({T[m.group(1)]} *)(p + {m.group(2)}) = x; *({T[m.group(3)]} *)(p + {m.group(4)}) = y; }}"
    m=re.fullmatch(rf"li r3, (lbl_\w+)@sda21 ; blr",s)
    if m and var(m.group(1),f"extern u32 {m.group(1)};"): b=f"u32 *{f}(void) {{ return &{m.group(1)}; }}"
    m=re.fullmatch(rf"li r0, (lbl_\w+)@sda21 ; stw r0, (lbl_\w+)@sda21\(r0\) ; blr",s)
    if m and var(m.group(1),f"extern u32 {m.group(1)};") and var(m.group(2),f"extern u32 *{m.group(2)};"): b=f"void {f}(void) {{ {m.group(2)} = &{m.group(1)}; }}"
    m=re.fullmatch(rf"lis r4, (lbl_\w+)@ha ; addi r4, r4, (lbl_\w+)@l ; stw r4, {N}\(r3\) ; blr",s)
    if m and m.group(1)==m.group(2) and var(m.group(1),f"extern u8 {m.group(1)}[];"): b=f"void {f}(u8 *p) {{ *(u8 **)(p + {m.group(3)}) = {m.group(1)}; }}"
    m=re.fullmatch(rf"lis r3, (lbl_\w+)@ha ; addi r3, r3, (lbl_\w+)@l ; (lwz|lhz|lbz) r3, {N}\(r3\) ; blr",s)
    if m and m.group(1)==m.group(2) and var(m.group(1),f"extern u8 {m.group(1)}[];"): t=T[m.group(3)]; b=f"{t} {f}(void) {{ return *({t} *)({m.group(1)} + {m.group(4)}); }}"
    m=re.fullmatch(rf"lwz r3, {N}\(r3\) ; neg r0, r3 ; or r0, r0, r3 ; srwi r3, r0, 31 ; blr",s)
    if m: b=f"BOOL {f}(u8 *p) {{ return *(u32 *)(p + {m.group(1)}) != 0; }}"
    if b: code.append(b); gen_names.add(f)
# drop calls to functions generated in this same pass
code=[c for c in code if not any(re.search(r"\{ "+g+r"\(",c) for g in gen_names)]
protos={k:v for k,v in protos.items() if k not in gen_names and any(re.search(r"\{ "+k+r"\(",c) for c in code)}
print(f"{unit}: {len(code)}")
if apply and code:
    open(src,"a").write("\n// Simple functions, second pass (tail calls with arguments, constant stores)\n#include \"common.hpp\"\n\nextern \"C\" {\n\n"+"\n".join(list(vars_.values())+list(protos.values()))+"\n\n"+"\n".join(code)+"\n\n}\n")
