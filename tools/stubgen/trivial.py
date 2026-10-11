# Usage: python3 tools/stubgen/trivial.py src/.unsorted/<ADDR> [--apply]
# Writes placeholder C for trivial functions of a unit (stubs, getters, tail calls).
# The output is scaffolding: it is replaced when the unit is decompiled for real.
import re,sys,subprocess,os
ROOT=os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
unit=sys.argv[1]  # e.g. src/.unsorted/80007940
apply="--apply" in sys.argv
tgt=f"{ROOT}/build/RPBP01/obj/{unit}.o"
out=os.path.join(os.environ.get("TMPDIR","/tmp"),"gen_trivial.s")
subprocess.run([f"{ROOT}/build/tools/dtk","elf","disasm",tgt,out],capture_output=True)
src=f"{ROOT}/{unit}.cpp"
existing=open(src).read() if os.path.exists(src) else ""
fns={};cur=None
for l in open(out):
    m=re.match(r"\.fn (\S+), (\w+)",l)
    if m: cur=m.group(1); fns[cur]=[]; continue
    if l.startswith(".endfn"): cur=None; continue
    if cur:
        m=re.match(r"/\* [0-9A-F]+ [0-9A-F]+  [0-9A-F ]+ \*/\t(.*)",l)
        if m: fns[cur].append(m.group(1).strip())
        elif l.startswith(".L"): fns[cur].append("LABEL")
ext=set(); code=[]
LD={"lwz":"u32","lhz":"u16","lha":"s16","lbz":"u8","lfs":"f32"}
ST={"stw":"u32","sth":"u16","stb":"u8","stfs":"f32"}
def dec(name,decl):
    ext.add(decl)
n=0
for f,ins in fns.items():
    if not re.fullmatch(r"fn_[0-9A-F]{8}",f): continue
    if re.search(r"\b"+f+r"\b",existing): continue
    body=None
    if ins==["blr"]: body=f"void {f}(void) {{}}"
    elif len(ins)==2 and ins[1]=="blr":
        a=ins[0]
        m=re.fullmatch(r"li r3, (-?0x[0-9a-f]+|-?\d+)",a)
        if m: body=f"s32 {f}(void) {{ return {int(m.group(1),0)}; }}"
        m=re.fullmatch(r"(lwz|lhz|lha|lbz) r3, (\w+)@sda21\(r0\)",a)
        if m and m.group(2).startswith("lbl_"):
            t=LD[m.group(1)]; dec(m.group(2),f"extern {t} {m.group(2)};"); body=f"{t} {f}(void) {{ return {m.group(2)}; }}"
        m=re.fullmatch(r"lfs f1, (\w+)@sda21\(r0\)",a)
        if m and m.group(1).startswith("lbl_"):
            dec(m.group(1),f"extern f32 {m.group(1)};"); body=f"f32 {f}(void) {{ return {m.group(1)}; }}"
        m=re.fullmatch(r"(stw|sth|stb) r3, (\w+)@sda21\(r0\)",a)
        if m and m.group(2).startswith("lbl_"):
            t=ST[m.group(1)]; dec(m.group(2),f"extern {t} {m.group(2)};"); body=f"void {f}({t} v) {{ {m.group(2)} = v; }}"
        m=re.fullmatch(r"(lwz|lhz|lha|lbz) r3, (0x[0-9a-f]+|\d+)\(r3\)",a)
        if m: t=LD[m.group(1)]; body=f"{t} {f}(u8 *p) {{ return *({t} *)(p + {m.group(2)}); }}"
        m=re.fullmatch(r"lfs f1, (0x[0-9a-f]+|\d+)\(r3\)",a)
        if m: body=f"f32 {f}(u8 *p) {{ return *(f32 *)(p + {m.group(1)}); }}"
        m=re.fullmatch(r"(stw|sth|stb) r4, (0x[0-9a-f]+|\d+)\(r3\)",a)
        if m: t=ST[m.group(1)]; body=f"void {f}(u8 *p, {t} v) {{ *({t} *)(p + {m.group(2)}) = v; }}"
        m=re.fullmatch(r"stfs f1, (0x[0-9a-f]+|\d+)\(r3\)",a)
        if m: body=f"void {f}(u8 *p, f32 v) {{ *(f32 *)(p + {m.group(1)}) = v; }}"
        m=re.fullmatch(r"addi r3, r3, (0x[0-9a-f]+|\d+)",a)
        if m: body=f"u8 *{f}(u8 *p) {{ return p + {m.group(1)}; }}"
    elif len(ins)==1:
        m=re.fullmatch(r"b (fn_[0-9A-F]{8})",ins[0])
        if m: dec(m.group(1),f"void {m.group(1)}();"); body=f"void {f}(void) {{ {m.group(1)}(); }}"
    elif len(ins)==3 and ins[2]=="blr":
        m1=re.fullmatch(r"lis r3, (lbl_\w+)@ha",ins[0]); m2=re.fullmatch(r"addi r3, r3, (lbl_\w+)@l",ins[1])
        if m1 and m2 and m1.group(1)==m2.group(1):
            dec(m1.group(1),f"extern u8 {m1.group(1)}[];"); body=f"u8 *{f}(void) {{ return {m1.group(1)}; }}"
        m1=re.fullmatch(r"(lwz|lhz|lha|lbz) r3, (\w+)@sda21\(r0\)",ins[0]); m2=re.fullmatch(r"(lwz|lhz|lha|lbz) r3, (0x[0-9a-f]+|\d+)\(r3\)",ins[1])
        if m1 and m2 and m1.group(2).startswith("lbl_") and m1.group(1)=="lwz":
            t=LD[m2.group(1)]; dec(m1.group(2),f"extern u8 *{m1.group(2)};"); body=f"{t} {f}(void) {{ return *({t} *)({m1.group(2)} + {m2.group(2)}); }}"
        m1=re.fullmatch(r"(lwz) r3, (0x[0-9a-f]+|\d+)\(r3\)",ins[0]); m2=re.fullmatch(r"(lwz|lhz|lha|lbz) r3, (0x[0-9a-f]+|\d+)\(r3\)",ins[1])
        if m1 and m2:
            t=LD[m2.group(1)]; body=f"{t} {f}(u8 *p) {{ return *({t} *)(*(u8 **)(p + {m1.group(2)}) + {m2.group(2)}); }}"
    if body: code.append(body); n+=1
defined=set(re.findall(r"\b(fn_[0-9A-F]{8})\(",existing))|set(re.match(r"[\w ]+?\*?(fn_[0-9A-F]{8})\(",c).group(1) for c in code)
code=[c for c in code if not (re.search(r"\{ (fn_[0-9A-F]{8})\(\); \}",c) and re.search(r"\{ (fn_[0-9A-F]{8})\(\); \}",c).group(1) in defined)]
ext=set(e for e in ext if not (e.startswith("void fn_") and e[5:16] in defined))
n=len(code)
# skip symbols already declared in the file
ext=[e for e in sorted(ext) if not re.search(r"\b"+re.search(r"(fn|lbl)_\w+",e).group(0)+r"\b",existing)]
print(f"{unit}: generated {n} of {len(fns)} functions")
if apply and n:
    blk="\n// Simple functions (getters, stubs, tail calls)\n#include \"common.hpp\"\n\nextern \"C\" {\n\n"+"\n".join(ext)+("\n\n" if ext else "")+"\n".join(code)+"\n\n}\n"
    open(src,"a").write(blk)
