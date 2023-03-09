#include <list>
#include "jumandic/shared/juman_format.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Morpheme
{
    jumanpp::StringPiece surface;
    jumanpp::StringPiece reading;
    jumanpp::StringPiece pos;
    jumanpp::StringPiece subpos;
    jumanpp::StringPiece conjForm;
    jumanpp::StringPiece conjType;
    jumanpp::StringPiece baseForm;
    jumanpp::StringPiece pronunciation;
};

std::list<Morpheme> analyze(const char * model, const char * text);

#ifdef __cplusplus
}
#endif