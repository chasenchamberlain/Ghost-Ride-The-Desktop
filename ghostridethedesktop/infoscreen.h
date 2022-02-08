#ifndef INFOSCREEN_H
#define INFOSCREEN_H

#include "screen.h"
#include <QFile>

class InfoScreen : public Screen
{
private:
    const string welcome = "Welcome to my world! I'm Ghosty, and I'm \nhere to help set up your new \ncomputer. \n\nComputers help us do so many useful \nthings, but have you ever wondered \nhow they work? Get ready, because \nyou're about to find out!";
    const string info1 = "Welcome to your computer, today we will \nconfigure the 5 most important parts of \nthe computer: the Power Supply, Cooling \nSystem, CPU, GPU, and RAM. Don't worry \nif you haven't heard of these before, by \nthe end of the game you'll be a master! \n\nInteract with the components in each \nroom to complete minigames and build \nyour computer.";
    const string pwr =  "Welcome to the Power Supply! The \nPower Supply has a simple goal: convert \nthe AC power from the cord to low-\nvoltage regulated DC power for the \ncomputer. Failure to convert power risks \nfrying your computer. \n\nCollect the charges to power up your \ncomputer!";
    const string cooling = "This is the Cooling System! With so \nmany parts using so much power, \ncomputers can get really hot! The Cooling \nSystem uses either a fan or a liquid \ncooling setup to keep the CPU cool \nenough to work. \n\nMake sure your computer doesn't \noverheat! Route the cooling to the chip.";
    const string info2 = "Stuck? \n\nTry interacting with the computer \ncomponents to complete minigames. \n\nIf you are done with the minigames, \nhead to the room next to RAM \nto pick up your Operating System \nand complete your computer.";
    const string cpu = "This is a CPU! CPU stands for Central\nProcessing Unit. It performs the basic \narithmetical, logical, and input/output \noperations of a computer system. \n\nIn order to configure your CPU, \nyou must complete a series of basic \nmath questions. Since the CPU is in \ncharge of arithmetic, you must train it \nto be smart!";
    const string gpu = "Welcome to the GPU! GPU stands for \nGraphical Processing Unit. Everything you \nsee on your computer screen is made by \nthe GPU! \n\nUnfortunately, your GPU is uncalibrated \nand you need to help it decode images. \nSolve the sliding tile puzzle to \ncomplete your GPU.";
    const string info3 = "Stuck? \n\nTry interacting with the computer \ncomponents to complete minigames. \n\nIf you are done with the minigames, \nhead to the room next to RAM \nto pick up your Operating System \nand complete your computer.";
    const string ram = "This RAM! RAM stands for Random Access \nMemory, this is temporary storage \nthat your computer uses to very quickly \naccess data that it needs. RAM has \nlimited size, but luckily computers \nare very smart and know when to store \ndata in RAM, or in normal storage. \n\nOrganize RAM's memory by matching the \ntiles.";


    string infos[9] = {welcome, info1, pwr, cooling, info2, cpu, gpu, info3, ram};
    string titles[9] = {"Welcome", "Info_Screen_1", "Power_Supply", "Cooling_System",
                        "Info_Screen_2", "Central_Processing_Unit",
                        "Graphical_Processing_Unit", "Info_Screen_3", "Random_Access_Memory"};

    string selectedText = infos[0];
    string selectedTitle = titles[0];

    int GetNextScreen(BackgroundManager& bgm);
public:
    InfoScreen();
    int Run (b2World& World, BackgroundManager& bgm);
};

#endif // INFOSCREEN_H
