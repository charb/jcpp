package jcpp.mavenplugin.code;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import jcpp.mavenplugin.code.history.PackageHistory;
import jcpp.mavenplugin.code.history.TupleHistory;
import jcpp.mavenplugin.code.reflect.PackageLoaderCodeGenerator;
import jcpp.mavenplugin.code.reflect.PackageReflectionCodeGenerator;


public class CppPackage implements Comparable<CppPackage> {

    private final String name;

    private final String namespace;

    private final CppPackage parentPackage;

    private final List<CppPackage> subPackages;

    private final List<CppFileTuple> cppFileTuples;

    private UpdaterContext updaterContext;

    private PackageHistory existingPackageHistory;

    private PackageHistory newPackageHistory;


    public CppPackage(String name, CppPackage parentPackage) {
        this.name = name;
        this.namespace = ((parentPackage == null) || parentPackage.getNamespace().isEmpty()) ? name : (parentPackage.getNamespace() + "::" + name);
        this.parentPackage = parentPackage;
        subPackages = new ArrayList<CppPackage>();
        cppFileTuples = new ArrayList<CppFileTuple>();

        if (parentPackage != null) {
            parentPackage.addSubPackage(this);
        }
    }


    public void accept(ICppPackageVisitor visitor) {
        visitor.startCppPackage(this);

        for (CppPackage subPackage : subPackages) {
            subPackage.accept(visitor);
        }

        for (CppFileTuple tuple : cppFileTuples) {
            visitor.visitCppFileTuple(tuple);
        }

        visitor.endCppPackage(this);
    }

    public void sort() {
        Collections.sort(subPackages);
        Collections.sort(cppFileTuples);
        for (CppPackage cppPackage : subPackages) {
            cppPackage.sort();
        }
    }

    public void init(UpdaterContext updaterContext, PackageHistory existingPackageHistory) {
        this.updaterContext = updaterContext;
        this.existingPackageHistory = existingPackageHistory;

        if (existingPackageHistory != null) {
            existingPackageHistory.setCppPackage(this);
        }

        if (cppFileTuples.size() > 0) {
            List<TupleHistory> tuplesHistory = (existingPackageHistory == null) ? null : existingPackageHistory.getTuplesHistory();
            if ((tuplesHistory != null) && (tuplesHistory.size() > 0)) {
                int cppFileTuplesIndex = 0;
                int tupleHistoryIndex = 0;
                while ((tupleHistoryIndex < tuplesHistory.size()) && (cppFileTuplesIndex < cppFileTuples.size())) {
                    TupleHistory existingTupleHistory = tuplesHistory.get(tupleHistoryIndex);
                    CppFileTuple cppFileTuple = cppFileTuples.get(cppFileTuplesIndex);
                    int comparison = existingTupleHistory.getName().compareTo(cppFileTuple.getName());
                    if (comparison == 0) {
                        cppFileTuple.init(updaterContext, existingTupleHistory);
                        cppFileTuplesIndex++;
                        tupleHistoryIndex++;
                    } else if (comparison < 0) {
                        tupleHistoryIndex++;
                    } else {
                        cppFileTuple.init(updaterContext, null);
                        cppFileTuplesIndex++;
                    }
                }
                for (int i = cppFileTuplesIndex; i < cppFileTuples.size(); i++) {
                    cppFileTuples.get(i).init(updaterContext, null);
                }
            } else {
                for (CppFileTuple cppFileTuple : cppFileTuples) {
                    cppFileTuple.init(updaterContext, null);
                }
            }
        }

        if (subPackages.size() > 0) {
            List<PackageHistory> subPackagesHistory = (existingPackageHistory == null) ? null : existingPackageHistory.getSubPackagesHistory();
            if ((subPackagesHistory != null) && (subPackagesHistory.size() > 0)) {
                int subPackageIndex = 0;
                int packageHistoryIndex = 0;
                while ((packageHistoryIndex < subPackagesHistory.size()) && (subPackageIndex < subPackages.size())) {
                    PackageHistory packageHistory = subPackagesHistory.get(packageHistoryIndex);
                    CppPackage subPackage = subPackages.get(subPackageIndex);
                    int comparison = packageHistory.getName().compareTo(subPackage.getName());
                    if (comparison == 0) {
                        subPackage.init(updaterContext, packageHistory);
                        subPackageIndex++;
                        packageHistoryIndex++;
                    } else if (comparison < 0) {
                        packageHistoryIndex++;
                    } else {
                        subPackage.init(updaterContext, null);
                        subPackageIndex++;
                    }
                }
                for (int i = subPackageIndex; i < subPackages.size(); i++) {
                    subPackages.get(i).init(updaterContext, null);
                }
            } else {
                for (CppPackage subPackage : subPackages) {
                    subPackage.init(updaterContext, null);
                }
            }
        }

    }

    public boolean checkUpdated() {
        if (existingPackageHistory == null) {
            return true;
        }

        List<PackageHistory> subPackagesHistory = existingPackageHistory.getSubPackagesHistory();
        if (subPackagesHistory != null) {
            for (PackageHistory subPackageHistory : subPackagesHistory) {
                if (subPackageHistory.getCppPackage() == null) {
                    return true;
                }
            }
        }

        List<TupleHistory> tuplesHistory = existingPackageHistory.getTuplesHistory();
        if (tuplesHistory != null) {
            for (TupleHistory tupleHistory : tuplesHistory) {
                if (tupleHistory.getCppFileTuple() == null) {
                    return true;
                }
            }
        }

        for (CppPackage subPackage : subPackages) {
            if (subPackage.getExistingPackageHistory() == null) {
                return true;
            }
        }

        for (CppFileTuple tuple : cppFileTuples) {
            if ((tuple.getExistingTupleHistory() == null) || (tuple.getHeaderCPPFile() != null) || (tuple.getCppCPPFile() != null)) {
                return true;
            }
        }

        return false;
    }

    public void update() throws Exception {
        List<CppFileTuple> generatedCode = generateCode();
        newPackageHistory = createPackageHistory(generatedCode);
    }

    public void deleteExistingHistoryFiles() {
        if (existingPackageHistory != null) {
            existingPackageHistory.deletePackageGeneratedTuples(updaterContext.getNewHeaderBaseDir(), updaterContext.getNewCppBaseDir());
        }
    }

    public PackageHistory createNewHistoryFromExisting() {
        PackageHistory packageHistory = existingPackageHistory.createNewHistoryFromExisting();
        packageHistory.setCppPackage(this);

        for (CppPackage subPackage : subPackages) {
            packageHistory.addSubPackageHistory(subPackage.getNewPackageHistory());
        }

        for (CppFileTuple tuple : cppFileTuples) {
            packageHistory.addTupleHistory(tuple.getNewTupleHistory());
        }

        return packageHistory;
    }

    public UpdaterContext getUpdaterContext() {
        return updaterContext;
    }

    public PackageHistory getExistingPackageHistory() {
        return existingPackageHistory;
    }

    public String getName() {
        return name;
    }

    public String getNamespace() {
        return namespace;
    }

    public CppPackage getParentPackage() {
        return parentPackage;
    }

    public List<CppPackage> getSubPackages() {
        return subPackages;
    }

    public void addSubPackage(CppPackage subPackage) {
        subPackages.add(subPackage);
    }

    public List<CppFileTuple> getCppFileTuples() {
        return cppFileTuples;
    }

    public void addCPPFileTuple(CppFileTuple cppFileTuple) {
        cppFileTuples.add(cppFileTuple);
    }

    public PackageHistory getNewPackageHistory() {
        return newPackageHistory;
    }

    public void setNewPackageHistory(PackageHistory newPackageHistory) {
        this.newPackageHistory = newPackageHistory;
    }

    @Override
    public int compareTo(CppPackage o) {
        return name.compareTo(o.name);
    }

    protected PackageHistory createPackageHistory(List<CppFileTuple> generatedCode) throws Exception {
        PackageHistory packageHistory = new PackageHistory(name, namespace);

        for (CppFileTuple cppFileTuple : cppFileTuples) {
            packageHistory.addTupleHistory(cppFileTuple.getNewTupleHistory());
        }

        for (CppPackage subPackage : subPackages) {
            packageHistory.addSubPackageHistory(subPackage.getNewPackageHistory());
        }

        if ((generatedCode != null) && (generatedCode.size() > 0)) {
            for (CppFileTuple generatedCppFileTuple : generatedCode) {
                packageHistory.addGeneratedTupleHistory(generatedCppFileTuple.createTupleHistory(null));
            }
        }

        return packageHistory;
    }

    protected List<CppFileTuple> generateCode() throws Exception {
        List<CppFileTuple> generatedTuples = new ArrayList<CppFileTuple>();

        List<ICppCodeGenerator<CppPackage>> codeGenerators = createCppCodeGenerators();
        for (ICppCodeGenerator<CppPackage> codeGenerator : codeGenerators) {
            CppFileTuple generatedTuple = codeGenerator.generateCode(updaterContext, this);
            if (generatedTuple != null) {
                generatedTuples.add(generatedTuple);
            }
        }

        return generatedTuples;
    }

    protected List<ICppCodeGenerator<CppPackage>> createCppCodeGenerators() {
        List<ICppCodeGenerator<CppPackage>> list = new ArrayList<ICppCodeGenerator<CppPackage>>();

        if (updaterContext.isAddReflectionCode()) {
            list.add(PackageLoaderCodeGenerator.getInstance());
            list.add(PackageReflectionCodeGenerator.getInstance());
        }

        return list;
    }

}
