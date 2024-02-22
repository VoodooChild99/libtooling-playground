#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/PreprocessorOptions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/TargetSelect.h"

using namespace clang::tooling;

namespace {

static llvm::cl::OptionCategory ToolCategory("my-toy-tool options");

static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);
static llvm::cl::extrahelp MoreHelp("\nMore help text...\n");

static void InitializeLLVM() {
  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();
  llvm::InitializeAllDisassemblers();
}

static llvm::Expected<CommonOptionsParser>
createOptionParser(int argc, const char **argv) {
  std::vector<std::string> ArgVec;
  for (int i = 0; i < argc; ++i) {
    ArgVec.push_back(argv[i]);
  }
  ArgVec.push_back("--extra-arg");
  ArgVec.push_back("-I");
  ArgVec.push_back("--extra-arg");
  ArgVec.push_back(LIBTOOLING_INCLUDE_PATH);

  std::vector<const char *> Argv;
  for (const auto &Arg : ArgVec) {
    Argv.push_back(Arg.c_str());
  }
  int Argc = Argv.size();

  return CommonOptionsParser::create(Argc, Argv.data(), ToolCategory);
}

} // namespace

int main(int argc, const char **argv) {
  InitializeLLVM();

  auto OptionsParser = createOptionParser(argc, argv);
  if (auto E = OptionsParser.takeError()) {
    llvm::errs() << "Problem creating CommonOptionsParser: "
                 << llvm::toString(std::move(E)) << "\n";
    return 1;
  }
  ClangTool Tool(OptionsParser->getCompilations(),
                 OptionsParser->getSourcePathList());
  Tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get());
}