/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   backward_solid_svg;
    const int            backward_solid_svgSize = 756;

    extern const char*   cyan_knob_png;
    const int            cyan_knob_pngSize = 2577006;

    extern const char*   cyan_slider_png;
    const int            cyan_slider_pngSize = 5572;

    extern const char*   forward_solid_svg;
    const int            forward_solid_svgSize = 755;

    extern const char*   orange_knob_png;
    const int            orange_knob_pngSize = 2616653;

    extern const char*   orange_slider_png;
    const int            orange_slider_pngSize = 4136;

    extern const char*   pause_solid_svg;
    const int            pause_solid_svgSize = 661;

    extern const char*   play_solid_svg;
    const int            play_solid_svgSize = 593;

    extern const char*   repeat_solid_svg;
    const int            repeat_solid_svgSize = 919;

    extern const char*   stop_solid_svg;
    const int            stop_solid_svgSize = 554;

    extern const char*   trash_solid_svg;
    const int            trash_solid_svgSize = 707;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 11;

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
