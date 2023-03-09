// Inspired from https://github.com/eiennohito/jumanpp-t9

#include <string>
#include <list>
#include <stdexcept>
#include <iostream>
#include "core/env.h"
#include "core/analysis/analysis_result.h"
#include "./main.h"

void parse(const jumanpp::core::analysis::Analyzer &analyzer, std::list<Morpheme> &morphemes)
{
    jumanpp::core::analysis::AnalysisResult result;
    jumanpp::core::analysis::AnalysisPath path;
    jumanpp::core::analysis::NodeWalker walker;
    jumanpp::jumandic::output::JumandicFields fields;
    std::cout << "result.reset: " << result.reset(analyzer) << std::endl;
    std::cout << "result.fillTop1: " << result.fillTop1(&path) << std::endl;
    auto &output = analyzer.output();
    std::cout << "fields.initialize: " << fields.initialize(output) << std::endl;
    while (path.nextBoundary())
    {
        jumanpp::core::analysis::ConnectionPtr cptr{};
        if (
            !path.nextNode(&cptr) || !output.locate(cptr.latticeNodePtr(), &walker) || !walker.next())
        {
            std::cout << "SKIP" << std::endl;
            return;
        }
        Morpheme morpheme;
        morpheme.surface = fields.surface[walker];
        morpheme.reading = fields.reading[walker];
        morpheme.pos = fields.pos[walker];
        morpheme.subpos = fields.subpos[walker];
        morpheme.conjForm = fields.conjForm[walker];
        morpheme.conjType = fields.conjType[walker];
        morpheme.baseForm = fields.baseform[walker];
        morpheme.pronunciation = fields.surface[walker];
        std::cout << morpheme.surface << " " << morpheme.pos << std::endl;
        morphemes.push_back(morpheme);
    }
}

std::list<Morpheme> analyze(const char * model, const std::string &text)
{
    jumanpp::core::JumanppEnv env;
    if (!env.loadModel(jumanpp::StringPiece::fromCString(model)))
    {
        throw std::runtime_error("Failed to load Juman++ model");
    }

    env.setGlobalBeam(6, 10, 5);

    if (!env.initFeatures(nullptr))
    {
        throw std::runtime_error("Failed to initialize Juman++ features");
    }

    jumanpp::core::analysis::Analyzer analyzer;
    if (!env.makeAnalyzer(&analyzer))
    {
        throw std::runtime_error("Failed to make Juman++ analyzer");
    }

    std::list<Morpheme> morphemes;
    if (!analyzer.analyze(text))
    {
        return morphemes;
    }
    parse(analyzer, morphemes);

    return morphemes;
}

int main() {
    analyze("/Users/rav/repos/github/jumanppy/jumandic.jppmdl", "相手の名前はよく分かりませんでした、すみません。");
}