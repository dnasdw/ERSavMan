/*
 * Copyright (c) 2022 Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

struct SaveSlot {
    enum SlotType {
        Character,
        Summary,
        Other,
    };
    SlotType slotType;
    uint32_t offset;
    std::vector<uint8_t> data;
    uint8_t md5hash[16];
    std::wstring filename;
};

struct CharSlot: SaveSlot {
    std::wstring charname;
    uint16_t level;
    int useridOffset;
    uint64_t userid;
};

struct SummarySlot: SaveSlot {
    uint64_t userid;
    std::vector<std::pair<std::string, int>> charInfo;
};

class SaveFile {
public:
    enum SaveType {
        Steam,
        PS4,
    };
    explicit SaveFile(const std::string &filename);
    [[nodiscard]] inline bool ok() const { return ok_; }
    bool verifyMD5();
    bool exportToFile(const std::string &filename, int slot);
    bool importFromFile(const std::string &filename, int slot);
    void listSlots(int slot = -1);

private:
    void listSlot(int slot);

private:
    bool ok_ = false;
    std::string filename_;
    SaveType saveType_ = Steam;
    std::vector<uint8_t> header_;
    std::vector<std::unique_ptr<SaveSlot>> slots_;
};
