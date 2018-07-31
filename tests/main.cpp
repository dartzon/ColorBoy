#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "console.h"
#include "consts.h"
#include <fstream>
#include <string>


/// \brief internal class to load a ROM from a file
class ROMLoader
{
    const std::string m_filename;
    Console m_GBConsole;
public:
    
    explicit ROMLoader(const std::string& inFilename)
    :m_filename(inFilename)
    ,m_GBConsole(GBType::GBT_gbc)
    {
        std::fstream rom_file(sROMFolderPath + "/" + m_filename , std::ios::in | std::ios::binary);
        if(rom_file.is_open())
        {
            auto getFileLen =[&]()->size_t{
                std::streampos begin,end;
                begin = rom_file.tellg();
                rom_file.seekg (0, std::ios::end);
                end = rom_file.tellg();
                size_t size = end - begin;
                rom_file.seekg(0,std::ios::beg);
                return size;
            };
            MemoryType& memory = m_GBConsole.getMemory();
            rom_file.read((char*)memory.data(),getFileLen());
            
            rom_file.close();
        }
    }
    
    /// \brief get internal Console
    Console& getConsole(){
        
        return m_GBConsole;
    }
    
};



TEST_CASE("console load rom", "[Console:Memory]")
{
    ROMLoader romLoader("bios.gb");
    
    MemoryType& memory = romLoader.getConsole().getMemory();
    
    REQUIRE(memory.size() == GBConfig::sysMemSize); ///< dummy test, should always pass
    
    Console& console = romLoader.getConsole();
    console.runOnce();
    //TBD: check PC, SP & flags
}

