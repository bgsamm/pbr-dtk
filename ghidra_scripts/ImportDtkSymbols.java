// Imports config/RPBP01/symbols.txt (decomp-toolkit format) into the current program.
// Functions are created if needed and renamed; objects and labels get a primary label.
// Generic names (fn_/lbl_) are skipped.
// @category PBR

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;

import java.io.File;
import java.nio.file.Files;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ImportDtkSymbols extends GhidraScript {
    private static final Pattern LINE = Pattern.compile(
        "^(\\S+)\\s*=\\s*[^:]+:0x([0-9A-Fa-f]+);\\s*//\\s*type:(\\w+).*$");

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        File file = args.length > 0 ? new File(args[0]) : askFile("symbols.txt", "Import");
        List<String> lines = Files.readAllLines(file.toPath());
        int funcs = 0, labels = 0, skipped = 0;
        for (String line : lines) {
            if (monitor.isCancelled()) break;
            Matcher m = LINE.matcher(line.trim());
            if (!m.matches()) continue;
            String name = m.group(1);
            String type = m.group(3);
            if (name.startsWith("fn_") || name.startsWith("lbl_")) { skipped++; continue; }
            Address addr = toAddr(Long.parseLong(m.group(2), 16));
            try {
                if (type.equals("function")) {
                    Function f = getFunctionAt(addr);
                    if (f == null) {
                        disassemble(addr);
                        f = createFunction(addr, name);
                    }
                    if (f != null) {
                        f.setName(name, SourceType.IMPORTED);
                        funcs++;
                        continue;
                    }
                }
                createLabel(addr, name, true, SourceType.IMPORTED);
                labels++;
            } catch (Exception e) {
                printerr(name + " @ " + addr + " : " + e.getMessage());
            }
        }
        println("Functions named: " + funcs + ", labels: " + labels + ", generic names skipped: " + skipped);
    }
}
