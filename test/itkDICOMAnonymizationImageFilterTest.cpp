#include <fstream>
#include <map>
#include <sstream>
#include <string>

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

typedef std::map<DcmTagKey, ElementFilter> ElementFilters;


ElementFilters parseProfile(const char* profile)
{
    std::ifstream ifs(profile);
    std::string line;
    ElementFilters filters;

    const DcmDataDictionary& dict = dcmDataDict.rdlock();
    dcmDataDict.unlock();

    while (std::getline(ifs, line))
    {
        const DcmDictEntry* entry = dict.findEntry(line.c_str());
        if (entry)
        {
            filters.insert(std::pair<DcmTagKey, ElementFilter>(
                entry->getKey(), ElementFilter(*entry, "TODO - operations")));
        }
        else
        {
            std::cerr << "WARNING: Tag not found in dictionary: " << line << std::endl;
        }
    }

    return filters;
}

void filterElements(DcmDataset* dataset, ElementFilters filters)
{
    DcmStack stack;
    DcmObject *dobj = NULL;
    DcmTagKey tag;
    OFCondition status = dataset->nextObject(stack, OFTrue);
    while (status.good())
    {
        dobj = stack.top();

        // Search the white list for this tag
        if(filters.find(dobj->getTag()) == filters.end())
        {
            std::cout << "Removing non-whitelisted tag: " << dobj->getTag() << std::endl;
            stack.pop();
            delete ((DcmItem *)(stack.top()))->remove(dobj);
        }

        status = dataset->nextObject(stack, OFTrue);
    }
}


void anonymize(const char* in, const char* out, const char* profile)
{
    // Read input image
    DcmFileFormat dff;
    OFCondition loadStatus = dff.loadFile(in);

    if (loadStatus.bad())
    {
        std::ostringstream msg;
        msg << "Unable to load file: " << in << std::endl;
        throw std::logic_error(msg.str());
    }

    // Parse profile to generate white list of elements
    auto filters = parseProfile(profile);

    DcmDataset* dataset = dff.getDataset();

    // Iterate over all tags, apply filters
    filterElements(dataset, filters);


    // Write the output file
    OFCondition saveStatus = dff.saveFile(out, EXS_LittleEndianExplicit);
    if (saveStatus.bad())
    {
        std::ostringstream msg;
        msg << "Unable to save filtered DICOM file: " << out << std::endl;
        throw std::logic_error(msg.str());
    }
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
