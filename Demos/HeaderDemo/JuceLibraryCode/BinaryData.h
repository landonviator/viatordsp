/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   dark_blue_png;
    const int            dark_blue_pngSize = 3938445;

    extern const char*   landon5503_png;
    const int            landon5503_pngSize = 28292;

    extern const char*   landon5504_png;
    const int            landon5504_pngSize = 26270;

    extern const char*   oscilloscope01_png;
    const int            oscilloscope01_pngSize = 466394;

    extern const char*   pluginBackground_png;
    const int            pluginBackground_pngSize = 8282212;

    extern const char*   pluginBackground2_png;
    const int            pluginBackground2_pngSize = 2893608;

    extern const char*   testTexture_png;
    const int            testTexture_pngSize = 3965203;

    extern const char*   TEXTURE5_png;
    const int            TEXTURE5_pngSize = 3515887;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
