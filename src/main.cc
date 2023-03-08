#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "core/env.h"
#include "core/analysis/analysis_result.h"

using namespace jumanpp;

struct Morpheme
{
    std::string surface;
    std::string reading;
    std::string pos;
    std::string subpos;
    std::string conjForm;
    std::string conjType;
    std::string baseForm;
    std::string pronunciation;
};

void parse(const core::analysis::Analyzer &analyzer)
{
    core::analysis::StringField surface;
    core::analysis::StringField english;
    core::analysis::AnalysisPath path;
    core::analysis::AnalysisResult result;
    core::analysis::NodeWalker walker;
    auto &output = analyzer.output();
    while (path.nextBoundary())
    {
        core::analysis::ConnectionPtr cptr{};
        if (
            !path.nextNode(&cptr) || !output.locate(cptr.latticeNodePtr(), &walker) || !walker.next())
        {
            return;
        }

        std::cout << surface[walker] << "\t" << english[walker] << "\n";
    }
    std::cout << std::endl;
}

std::vector<Morpheme> analyze(const std::string &text)
{
    core::JumanppEnv env;
    if (!env.loadModel(StringPiece::fromCString("/Users/rav/repos/github/jumanppy/jumandic.jppmdl")))
    {
        throw std::runtime_error("Failed to load Juman++ model");
    }

    env.setBeamSize(5);
    env.setGlobalBeam(6, 1, 5);

    if (!env.initFeatures(nullptr))
    {
        throw std::runtime_error("Failed to initialize Juman++ features");
    }

    core::analysis::Analyzer analyzer;
    if (!env.makeAnalyzer(&analyzer))
    {
        throw std::runtime_error("Failed to make Juman++ analyzer");
    }

    std::vector<Morpheme> morphemes;
    if (!analyzer.analyze(text))
    {
        return morphemes;
    }
    core::analysis::AnalysisResult result;
    core::analysis::NodeWalker walker;
    core::analysis::ConnectionPtr connection;
    auto &output = analyzer.output();

    return morphemes;
}

int main() {
    analyze("魅力がたっぷりと詰まっている");
}