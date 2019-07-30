#include "hamming_encoder_lib.h"
#include "turbo_coder_lib.h"
#include <memory>

enum ENCODERTYPE
{
    HAMMING,
    TURBO
};

class EncoderFactory
{
public:
    EncoderFactory() = delete;

    static std::shared_ptr<I_Encoder> CreateEncoder(const ENCODERTYPE& kType)
    {
        switch (kType)
        {
        case HAMMING:
        {
            return std::make_shared<Hamming_Encoder74>();
            break;
        }
        case TURBO:
        {
            return std::make_shared<Turbo_Encoder>();
            break;
        }
        default:
            std::cerr << "Invalid!"; exit(1);
            break;
        }
    }
};