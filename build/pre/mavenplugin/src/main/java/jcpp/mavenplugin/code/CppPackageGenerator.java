package jcpp.mavenplugin.code;

import java.io.File;
import java.io.IOException;

import java.util.Arrays;
import java.util.Comparator;


public class CppPackageGenerator {

    private final File includeRootFile;
    private final File cppRootFile;


    public CppPackageGenerator(File includeRootFile, File cppRootFile) throws IOException {
        this.includeRootFile = includeRootFile.getCanonicalFile();
        this.cppRootFile = cppRootFile.getCanonicalFile();
    }


    public CppPackage generateCPPPackage() throws IOException {
        CppPackage cppPackage = new CppPackage("", null);
        findTuples(includeRootFile, cppRootFile, cppPackage);
        cppPackage.sort();
        return cppPackage;
    }

    protected void findTuples(File headerDir, File cppDir, CppPackage cppPackage) throws IOException {
        File[] headerFiles = (headerDir == null) ? null : headerDir.listFiles();
        if (headerFiles == null) {
            headerFiles = new File[0];
        } else if (headerFiles.length > 0) {
            Arrays.sort(headerFiles, FileNameComparator.getInstance());
        }

        File[] cppFiles = (cppDir == null) ? null : cppDir.listFiles();
        if (cppFiles == null) {
            cppFiles = new File[0];
        } else if (cppFiles.length > 0) {
            Arrays.sort(cppFiles, FileNameComparator.getInstance());
        }

        int headerIndex = 0;
        int cppIndex = 0;

        while ((headerIndex != headerFiles.length) && (cppIndex != cppFiles.length)) {
            File headerFile = headerFiles[headerIndex];
            File cppFile = cppFiles[cppIndex];

            if (headerFile.isFile() && !Utils.isCodeFile(headerFile)) {
                headerIndex++;
                continue;
            }

            if (cppFile.isFile() && !Utils.isCodeFile(cppFile)) {
                cppIndex++;
                continue;
            }

            if (headerFile.isFile() && cppFile.isFile()) {
                String headerClassName = Utils.getCodeClassName(headerFile);
                String cppClassName = Utils.getCodeClassName(cppFile);

                if (headerClassName.equals(cppClassName)) {
                    headerIndex++;
                    cppIndex++;
                    new CppFileTuple(Utils.getCodeClassName(headerFile), getNamespace(headerFile, true), headerFile, cppFile, cppPackage);
                } else {
                    if (headerClassName.compareTo(cppClassName) < 0) {
                        headerIndex++;
                        new CppFileTuple(Utils.getCodeClassName(headerFile), getNamespace(headerFile, true), headerFile, null, cppPackage);
                    } else {
                        cppIndex++;
                        new CppFileTuple(Utils.getCodeClassName(cppFile), getNamespace(cppFile, false), null, cppFile, cppPackage);
                    }
                }
            } else if (headerFile.isDirectory() && cppFile.isDirectory()) {
                String headerDirName = headerFile.getName();
                String cppdDirName = cppFile.getName();
                if (headerDirName.equals(cppdDirName)) {
                    headerIndex++;
                    cppIndex++;
                    findTuples(headerFile, cppFile, new CppPackage(headerDirName, cppPackage));
                } else {
                    if (headerDirName.compareTo(cppdDirName) < 0) {
                        headerIndex++;
                        loopOverHeaderFiles(headerFile, new CppPackage(headerDirName, cppPackage));
                    } else {
                        cppIndex++;
                        loopOverCppFiles(cppFile, new CppPackage(cppdDirName, cppPackage));
                    }
                }
            } else {
                String headerFileName = headerFile.getName();
                String cppdFileName = cppFile.getName();
                if (headerFileName.equals(cppdFileName)) {
                    if (headerFile.isFile()) {
                        headerIndex++;
                        new CppFileTuple(Utils.getCodeClassName(headerFile), getNamespace(headerFile, true), headerFile, null, cppPackage);
                    } else {
                        cppIndex++;
                        new CppFileTuple(Utils.getCodeClassName(cppFile), getNamespace(cppFile, false), null, cppFile, cppPackage);
                    }
                } else {
                    if (headerFileName.compareTo(cppdFileName) < 0) {
                        headerIndex++;
                        if (headerFile.isFile()) {
                            new CppFileTuple(Utils.getCodeClassName(headerFile), getNamespace(headerFile, true), headerFile, null, cppPackage);
                        } else {
                            loopOverHeaderFiles(headerFile, new CppPackage(headerFileName, cppPackage));
                        }
                    } else {
                        cppIndex++;
                        if (cppFile.isFile()) {
                            new CppFileTuple(Utils.getCodeClassName(cppFile), getNamespace(cppFile, false), null, cppFile, cppPackage);
                        } else {
                            loopOverCppFiles(cppFile, new CppPackage(cppdFileName, cppPackage));
                        }
                    }
                }
            }
        }

        while (headerIndex != headerFiles.length) {
            File headerFile = headerFiles[headerIndex++];
            if (headerFile.isFile()) {
                if (Utils.isCodeFile(headerFile)) {
                    new CppFileTuple(Utils.getCodeClassName(headerFile), getNamespace(headerFile, true), headerFile, null, cppPackage);
                }
            } else {
                loopOverHeaderFiles(headerFile, new CppPackage(headerFile.getName(), cppPackage));
            }
        }

        while (cppIndex != cppFiles.length) {
            File cppFile = cppFiles[cppIndex++];
            if (cppFile.isFile()) {
                if (Utils.isCodeFile(cppFile)) {
                    new CppFileTuple(Utils.getCodeClassName(cppFile), getNamespace(cppFile, false), null, cppFile, cppPackage);
                }
            } else {
                loopOverCppFiles(cppFile, new CppPackage(cppFile.getName(), cppPackage));
            }
        }
    }

    protected void loopOverHeaderFiles(File headerDir, CppPackage cppPackage) throws IOException {
        for (File headerFile : headerDir.listFiles()) {
            if (headerFile.isFile()) {
                if (Utils.isCodeFile(headerFile)) {
                    new CppFileTuple(Utils.getCodeClassName(headerFile), getNamespace(headerFile, true), headerFile, null, cppPackage);
                }
            } else {
                loopOverHeaderFiles(headerFile, new CppPackage(headerFile.getName(), cppPackage));
            }
        }
    }

    protected void loopOverCppFiles(File cppDir, CppPackage cppPackage) throws IOException {
        for (File cppFile : cppDir.listFiles()) {
            if (cppFile.isFile()) {
                if (Utils.isCodeFile(cppFile)) {
                    new CppFileTuple(Utils.getCodeClassName(cppFile), getNamespace(cppFile, false), null, cppFile, cppPackage);
                }
            } else {
                loopOverCppFiles(cppFile, new CppPackage(cppFile.getName(), cppPackage));
            }
        }
    }

    protected String getNamespace(File codeFile, boolean headerFile) throws IOException {
        return Utils.getNamespace(codeFile, headerFile ? includeRootFile : cppRootFile);
    }


    public static class FileNameComparator implements Comparator<File> {
        private static final FileNameComparator instance = new FileNameComparator();


        private FileNameComparator() {
        }


        public static FileNameComparator getInstance() {
            return instance;
        }

        @Override
        public int compare(File o1, File o2) {
            return o1.getName().compareTo(o2.getName());
        }
    }

}
