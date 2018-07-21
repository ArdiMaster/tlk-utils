// MIT License
//
// Copyright (c) 2018 ArdiMaster
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>

#include "libtlk.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "USAGE: %s tlkfile [-i|newfile] \"text\"\n", argv[0]);
        return 1;
    }
    std::string originalFile(argv[1]);

    // Get language and element count without processing entire file
    uint32_t elements;
    FILE *in = fopen(argv[1], "r");
    if (in != NULL) {
        tlk::Header *header = (tlk::Header*) malloc(sizeof(tlk::Header));
        fread(header, sizeof(tlk::Header), 1, in);
        elements = header->StringCount;
        printf("%s: %s, %u entries\n", argv[1], tlk::GetLanguage(header->LanguageId), elements);
        fclose(in);
        free(header);
    } else {
        perror("Unable to open input file: ");
        return 1;
    }

    std::string newText(argv[3]);
    tlk::StringDataElement *newElement = new tlk::StringDataElement;
    newElement->Flags = 0x1;
    strcpy(newElement->SoundResRef, "");
    newElement->VolumeVariance = 0;
    newElement->PitchVariance = 0;
    /* OffsetToString and StringSize will be calculated automatically
     * upon write. */
    newElement->SoundLength = 0.0f;

    tlk::Builder builder(originalFile);
    builder.AddLine(newElement, newText);
    if(strcmp(argv[2], "-i") == 0) {
        builder.WriteFile(originalFile);
    } else {
        builder.WriteFile(argv[2]);
    }

    delete newElement;

    printf("Wrote Element #%d.\n", elements);

    return 0;
}
