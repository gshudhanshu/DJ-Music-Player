/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   backward_solid_svg;
    const int            backward_solid_svgSize = 553;

    extern const char*   forward_solid_svg;
    const int            forward_solid_svgSize = 553;

    extern const char*   pause_solid_svg;
    const int            pause_solid_svgSize = 460;

    extern const char*   play_solid_svg;
    const int            play_solid_svgSize = 394;

    extern const char*   repeat_solid_svg;
    const int            repeat_solid_svgSize = 705;

    extern const char*   stop_solid_svg;
    const int            stop_solid_svgSize = 355;

    extern const char*   trash_solid_svg;
    const int            trash_solid_svgSize = 502;

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
