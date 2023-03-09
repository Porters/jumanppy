// Inspired from https://github.com/eiennohito/jumanpp-t9

#include <algorithm>
#include <string>
#include <list>
#include <stdexcept>
#include <iostream>
#include "core/env.h"
#include "core/analysis/analysis_result.h"
#include "jumandic/shared/juman_format.h"
#include "main.h"

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
        morpheme.surface = fields.surface[walker].str().c_str();
        morpheme.reading = fields.reading[walker].str().c_str();
        morpheme.pos = fields.pos[walker].str().c_str();
        morpheme.subpos = fields.subpos[walker].str().c_str();
        morpheme.conjForm = fields.conjForm[walker].str().c_str();
        morpheme.conjType = fields.conjType[walker].str().c_str();
        morpheme.baseForm = fields.baseform[walker].str().c_str();
        morpheme.pronunciation = fields.surface[walker].str().c_str();
        std::cout << morpheme.surface << " " << morpheme.pos << std::endl;
        morphemes.push_back(morpheme);
    }
}

std::list<Morpheme> do_analyze(const char * model, const char * text)
{
    jumanpp::core::JumanppEnv env;
    std::cout << "Model: " << model << std::endl;
    std::cout << "Text: " << text << std::endl;
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
    std::string text_as_string = std::string(text);
    if (!analyzer.analyze(text_as_string))
    {
        return morphemes;
    }
    parse(analyzer, morphemes);

    return morphemes;
}

Morpheme * analyze(const char * model, const char * text)
{
    auto morphemes = do_analyze(model, text);
    auto morphemes_as_array = new Morpheme[morphemes.size()];
    std::copy(morphemes.begin(), morphemes.end(), morphemes_as_array);
    return morphemes_as_array;
}

// To test
int main() {
    analyze("/Users/rav/repos/github/jumanppy/jumandic.jppmdl", "相手の名前はよく分かりませんでした、すみません。");
}