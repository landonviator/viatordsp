/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Articulations_back_png;
    const int            Articulations_back_pngSize = 2194;

    extern const char*   Articulations_decore_png;
    const int            Articulations_decore_pngSize = 182598;

    extern const char*   background_png;
    const int            background_pngSize = 2682319;

    extern const char*   landon5504_png;
    const int            landon5504_pngSize = 26270;

    extern const char*   led_off_png;
    const int            led_off_pngSize = 9587;

    extern const char*   led_on_png;
    const int            led_on_pngSize = 11268;

    extern const char*   pluginBackground2_png;
    const int            pluginBackground2_pngSize = 2893608;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 7;

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
