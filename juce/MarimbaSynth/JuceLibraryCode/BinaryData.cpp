/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== autoeffect.dsp ==================
static const unsigned char temp_binary_data_0[] =
"    adapt(1,1) = _;\n"
"    adapt(2,2) = _,_;\n"
"    adapt(1,2) = _ <: _,_;\n"
"    adapt(2,1) = _,_ :> _;\n"
"\n"
"    adaptor(F,G) = adapt(outputs(F),inputs(G));\n"
"\n"
"    process = adaptor(library(\"marimba.dsp\").process, library(\"marimba.dsp\").effect) : library(\"marimba.dsp\").effect;\n";

const char* autoeffect_dsp = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x08de0d02:  numBytes = 264; return autoeffect_dsp;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "autoeffect_dsp"
};

const char* originalFilenames[] =
{
    "autoeffect.dsp"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
    {
        if (namedResourceList[i] == resourceNameUTF8)
            return originalFilenames[i];
    }

    return nullptr;
}

}
