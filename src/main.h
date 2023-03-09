#ifdef __cplusplus
extern "C" {
#endif

struct Morpheme
{
    const char * surface;
    const char * reading;
    const char * pos;
    const char * subpos;
    const char * conjForm;
    const char * conjType;
    const char * baseForm;
    const char * pronunciation;
};

Morpheme * analyze(const char * model, const char * text);

#ifdef __cplusplus
}
#endif
