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
#include <cstring>
#include <string>
#include <tuple>
#include <cstdlib>

#include "libtlk.h"

void safelyGetString(const tlk::FileView &view, const tlk::StringDataElement *element,
                     char **target) {
    std::tuple<const char*, uint32_t> content = view.GetCString(element);
    uint32_t len = std::get<1>(content);
    *target = (char*) calloc(len+1, sizeof(char));
    strncpy(*target, std::get<0>(content), len);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "USAGE: %s tlkfile \"searchstring\"\n", argv[0]);
        return 1;
    }

    tlk::FileView view(argv[1]);
    printf("%s: %s, %u entries.\n", argv[1],
        tlk::GetLanguage(view.GetHeader()->LanguageId), view.GetStringCount());

    int count = 0;
    char *content;
    const tlk::StringDataElement *elem;
    for (uint32_t i = 0; i < view.GetStringCount(); i++) {
        elem = view.GetStringElement(i);
        safelyGetString(view, elem, &content);
        if (strstr(content, argv[2]) != NULL) {
            printf("Element #%u:\n....... Flags: 0x%X\n....... "
                   "SoundResRef: %s\n....... VolumeVariance: %u\n....... "
                   "PitchVariance: %u\n....... OffsetToString: %u\n....... "
                   "StringSize: %u\n....... SoundLength: %f\n....... "
                   "Content: \"%s\"\n\n", i, elem->Flags, elem->SoundResRef,
                   elem->VolumeVariance, elem->PitchVariance,
                   elem->OffsetToString, elem->StringSize, elem->SoundLength,
                   content);
            count++;
        }
        free(content);
    }
    return 0;
}
