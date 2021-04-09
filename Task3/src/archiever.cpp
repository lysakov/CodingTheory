#include <algorithm>
#include <iostream>

#include "archiever.hpp"

void Archiever::zip(std::ostream &output)
{

    auto res = collectBytesStatistic();
    for (auto p: res) {

        output << p.first << ":" << p.second << '\n';

    }

}

std::vector<WordDesc> Archiever::collectBytesStatistic() 
{

    uint8_t i = 0;
    std::vector<std::pair<uint8_t, uint>> res = decltype(res)(256);
    std::for_each(res.begin(), res.end(), 
        [i](std::pair<uint8_t, uint> &p) mutable {p = std::pair<uint8_t, uint>(i, 0); ++i;});

    do
    {
        input->read(buffer, BUFFER_LEN);
        for (long int i = 0; i < input->gcount(); ++i) {
            res[static_cast<uint8_t>(buffer[i])].second += 1;
        }
    } while (input->gcount() != 0);

    input->seekg(std::ios_base::beg);
    std::sort(res.begin(), res.end(), 
        [](std::pair<uint8_t, uint> p1, std::pair<uint8_t, uint> p2) {return p1.second > p2.second;});

    return decltype(collectBytesStatistic())();

}