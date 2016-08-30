#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "dcdict.h"          /* DcmDataDictionary, dcmDataDict */
#include "dcdicent.h"        /* DicomDictEntry */
#include "dcuid.h"           /* SITE_INSTANCE_UID_ROOT */
#include "dcsequen.h"        /* for DcmSequenceOfItems */
#include "dcvrcs.h"          /* for DcmCodeString */
#include "dcvrfd.h"          /* for DcmFloatingPointDouble */
#include "dcvrfl.h"          /* for DcmFloatingPointDouble */
#include "dcvrsl.h"          /* for DCMSignedLong */
#include "dcvrus.h"          /* for DcmUnsignedShort */
#include "dcvris.h"          /* for DcmIntegerString */
#include "dcvrobow.h"        /* for DcmOtherByteOtherWord */
#include "dcvrui.h"          /* for DcmUniqueIdentifier */
#include "dcfilefo.h"        /* for DcmFileFormat */
#include "dcdeftag.h"        /* for DCM_NumberOfFrames */
#include "dcvrlo.h"          /* for DcmLongString */
#include "dcvrtm.h"          /* for DCMTime */
#include "dcvrda.h"          /* for DcmDate */
#include "dcvrpn.h"          /* for DcmPersonName */
//#include "dcmimage.h"        /* for DicomImage */


// A container for handling of a single element
struct ElementFilter
{
    ElementFilter(DcmDictEntry entry, std::string op) : entry(entry), op(op) {}

    DcmDictEntry entry;
    std::string op;
};


std::vector<ElementFilter> parseProfile(const char* profile)
{
    std::ifstream ifs(profile);
    std::string line;
    std::vector<ElementFilter> filters;

    const DcmDataDictionary& dict = dcmDataDict.rdlock();
    dcmDataDict.unlock();

    while (std::getline(ifs, line))
    {
        const DcmDictEntry* entry = dict.findEntry(line.c_str());
        if (entry)
        {
            filters.push_back(ElementFilter(*entry, "TODO - operations"));
        }
        else
        {
            std::cerr << "WARNING: Tag not found in dictionary: " << line << std::endl;
        }
    }

    return filters;
}


void anonymize(const char* in, const char* out, const char* profile)
{
    // Read input image
    DcmFileFormat inFormat;
    OFCondition loadStatus = inFormat.loadFile(in);

    if (loadStatus.bad())
    {
        std::ostringstream msg;
        msg << "Unable to load file: " << in << std::endl;
        throw std::logic_error(msg.str());
    }



    // Parse profile to generate white list of elements
    auto filters = parseProfile(profile);

    DcmFileFormat outFormat;
    DcmDataset* inData = inFormat.getDataset();
    DcmDataset* outData = outFormat.getDataset();

    // Create a new UID for the output dataset
    char uid[100];
    dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT);
    outData->putAndInsertString(DCM_SOPInstanceUID, uid);

    // Add whitelisted items to the output dataset
    for (auto filter : filters)
    {
        if (inData->tagExists(filter.entry))
        {
            std::cout << "Tag exists: " << filter.entry << std::endl;
        }
        else
        {
            std::cout << "Skipping tag, does not exist." << filter.entry << std::endl;
        }
    }

    // Copy pixel data to the output dataset
    /*dataset->putAndInsertUint8Array(DCM_PixelData, pixelData, pixelLength);

    // Write the output file
    OFCondition saveStatus = fileformat.saveFile(out, EXS_LittleEndianExplicit);
    if (saveStatus.bad())
    {
        std::ostringstream msg;
        msg << "Unable to save filtered DICOM file: " << out << std::endl;
        throw std::logic_error(msg.str());
    }*/
}


int itkDICOMAnonymizationImageFilterTest(int argc, char* argv[])
{
    const char* inputFile = argv[1];
    const char* outputFile = argv[2];
    const char* profile = argv[3];

    anonymize(inputFile, outputFile, profile);

    //std::cout << dcmDataDict << std::endl;

    return 0;
}
