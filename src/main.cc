// Inspired from https://github.com/eiennohito/jumanpp-t9

#include <algorithm>
#include <string>
#include <list>
#include <stdexcept>
#include <iostream>
#include "core/env.h"
#include "core/analysis/analysis_result.h"
#include "jumandic/shared/jumanpp_args.h"
#include "jumandic/shared/juman_format.h"
#include "util/logging.hpp"
#include "json.hpp"
#include "main.h"


auto defaultConf = jumanpp::jumandic::JumanppConf();

void parse(const jumanpp::core::analysis::Analyzer &analyzer, std::list<Morpheme> &morphemes)
{
    jumanpp::core::analysis::AnalysisResult result;
    jumanpp::core::analysis::AnalysisPath path;
    jumanpp::core::analysis::NodeWalker walker;
    jumanpp::jumandic::output::JumandicFields fields;
    auto &output = analyzer.output();
    if (
        !result.reset(analyzer).isOk() || !result.fillTop1(&path).isOk() || !fields.initialize(output).isOk())
    {
        throw std::runtime_error("Failed initialize parse");
    }
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
        morpheme.surface = fields.surface[walker].str();
        morpheme.reading = fields.reading[walker].str();
        morpheme.pos = fields.pos[walker].str();
        morpheme.subpos = fields.subpos[walker].str();
        morpheme.conjForm = fields.conjForm[walker].str();
        morpheme.conjType = fields.conjType[walker].str();
        morpheme.baseForm = fields.baseform[walker].str();
        morpheme.pronunciation = fields.surface[walker].str();
        morphemes.push_back(morpheme);
    }
}

std::list<Morpheme> doAnalyze(const char *model, const char *text)
{
    jumanpp::core::JumanppEnv env;
    if (!env.loadModel(jumanpp::StringPiece::fromCString(model)))
    {
        throw std::runtime_error("Failed to load Juman++ model");
    }

    env.setBeamSize(defaultConf.beamSize);
    env.setGlobalBeam(defaultConf.globalBeam, defaultConf.rightCheck, defaultConf.rightBeam);

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
    auto textAsString = std::string(text);
    if (!analyzer.analyze(textAsString))
    {
        return morphemes;
    }
    parse(analyzer, morphemes);

    return morphemes;
}

nlohmann::json listToJson(std::list<Morpheme> &morphemes)
{
    nlohmann::json jsonArray = nlohmann::json::array();
    for (const auto &morpheme : morphemes)
    {
        nlohmann::json jsonObject = {
            {"surface", morpheme.surface},
            {"reading", morpheme.reading},
            {"pos", morpheme.pos},
            {"subpos", morpheme.subpos},
            {"conjForm", morpheme.conjForm},
            {"conjType", morpheme.conjType},
            {"baseForm", morpheme.baseForm},
            {"pronunciation", morpheme.pronunciation}};
        jsonArray.push_back(jsonObject);
    }
    return jsonArray;
}

const char *analyze(const char *model, const char *text)
{
    jumanpp::util::logging::CurrentLogLevel = jumanpp::util::logging::Level::Warning;
    auto morphemes = doAnalyze(model, text);
    nlohmann::json json = listToJson(morphemes);
    std::string jsonString = json.dump();
    char *jsonCString = new char[jsonString.size() + 1];
    std::strcpy(jsonCString, jsonString.c_str());
    return jsonCString;
}

void free_memory(const char *ptr)
{
    delete[] ptr;
}

// To test
int main()
{
    std::cout << analyze("/Users/rav/repos/github/jumanppy/jumandic.jppmdl", "相手の名前はよく分かりませんでした、すみません。") << std::endl;
}