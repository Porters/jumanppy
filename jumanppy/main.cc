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

nlohmann::json parse(const jumanpp::core::analysis::Analyzer &analyzer)
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
    nlohmann::json morphemes = nlohmann::json::array();
    while (path.nextBoundary())
    {
        jumanpp::core::analysis::ConnectionPtr cptr{};
        if (
            !path.nextNode(&cptr) || !output.locate(cptr.latticeNodePtr(), &walker) || !walker.next())
        {
            break;
        }
        nlohmann::json morpheme = {
            {"surface", fields.surface[walker].str()},
            {"reading", fields.reading[walker].str()},
            {"pos", fields.pos[walker].str()},
            {"subpos", fields.subpos[walker].str()},
            {"conjForm", fields.conjForm[walker].str()},
            {"conjType", fields.conjType[walker].str()},
            {"baseForm", fields.baseform[walker].str()},
            {"pronunciation", fields.surface[walker].str()}
        };
        
        morphemes.push_back(morpheme);
    }
    return morphemes;
}

nlohmann::json doAnalyze(const char *model, const char *text)
{
    jumanpp::core::JumanppEnv env;
    if (!env.loadModel(jumanpp::StringPiece::fromCString(model)))
    {
        throw std::runtime_error("Failed to load Juman++ model");
    }

    // Default 5 6 1/5
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

    auto textAsString = std::string(text);
    if (!analyzer.analyze(textAsString))
    {
        return nlohmann::json::array();
    }
    return parse(analyzer);
}

const char *analyze(const char *model, const char *text)
{
    jumanpp::util::logging::CurrentLogLevel = jumanpp::util::logging::Level::Warning;
    std::string jsonString = doAnalyze(model, text).dump();
    char *jsonCString = new char[jsonString.size() + 1];
    std::strcpy(jsonCString, jsonString.c_str());
    return jsonCString;
}

// To test
int main()
{
    std::cout << analyze("./jumanppy/jumandic.jppmdl", "相手の名前はよく分かりませんでした、すみません。") << std::endl;
}