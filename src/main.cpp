#include <iostream>

#include <CoreGraphics/CoreGraphics.h>
#include <ImageIO/ImageIO.h>
#include <CoreFoundation/CoreFoundation.h>

#include "Image/Image.h"
#include "ArgParser.h"
#include "Processor/Processor.h"
#include "Serializer/Serializer.h"
#include "Rules/Rules.h"
#include "Rules/Validator.h"
#include "Rules/RulesParsing.h"
#include "Pattern/PatternExpander.h"

void PrintUsage() {
    std::cerr << "usage: slurps <Inputs> --output <Path> [-flags] [--argument <value>]\n\n";
    std::cerr << "    -r, --resampleMode <nearest/bilinear> - Specify resampling mode for operations\n\n";
    std::cerr << "    -f, --format <png, jpeg, icns> - Specify resampling mode for operations\n\n";
    std::cerr << "    -z, --newWidthHeight <Width>:<Height> - Change width & height of an image\n\n";
    std::cerr << "    -o, --output <Path> - Templated path for the output file. Available templates:\n";
    std::cerr << "                 <INDEX> - A counter number increasing with each processed file.\n";
    std::cerr << "                 <BASENAME> - Original name of the input file without extension.\n";
    std::cerr << "                 <EXT> - Original extension of the input file.\n";
    std::cerr << "                 <WIDTH> - Width of the output file.\n";
    std::cerr << "                 <HEIGHT> - Height of the output file.\n";
}

int main(int argc, char* argv[])
{
    ArgParser args(argc, argv);

    Rules rules{};
    std::string error;
    if(!ParseRules(args, rules, error)) {
        std::cerr << error << "\n";
        PrintUsage();
        return 1;
    }

    
    for(size_t inputIdx = 0; inputIdx < rules.inputs.size(); inputIdx++) {
        try {
            // TODO: Resolve output template
            std::string outputPath = PatternExpander::Expand(rules.output, rules.inputs[inputIdx], inputIdx, 0, 0);
            std::cout << rules.inputs[inputIdx] << " -> " << outputPath;

            // Load image
            Image img(rules.inputs[inputIdx]);
            
            // Process
            Processor processor(std::move(img));

            for(const auto& operation : rules.processingOperations) {
                processor.PerformOperation(operation.get());
            }

            // Save to disk
            ImageSerializer::SaveImageFile(processor.Finalize(), , rules.outputType);
            std::cout << " [OK]\n";
        } catch(const std::runtime_error& exc) {
            std::cout << " [FAILED]\n";
            std::cerr << exc.what() << "\n";
            return -1;
        }
    }

    return 0;
}