#pragma once

enum class ObjectID : uint8_t {
    Chaser		    = 0,
    Crumbs		    = 1,
    DiaPlatform		= 2,
    Diamond		    = 3,
    Door		    = 4,
    Finish		    = 5,
    Floor		    = 6,
    Fuel		    = 7,
    Hole		    = 8,
    Iceman		    = 9,
    JetPack		    = 10,
    Key		        = 11,
    Ladder		    = 12,
    Message		    = 13,
    Pillar		    = 14,
    Platform	    = 15,
    Portal		    = 16,
    Ramp		    = 17,
    Shield		    = 18,
    Slingshot	    = 19,
    Start		    = 20,
    Teleport	    = 21,
    TriPlatform 	= 22,
    TriWall		    = 23,
    Wall		    = 24,
    NUM_OBJECTS     = 25,
    
    Theme		    = 250,
    Weather		    = 251,
    Music		    = 252,
    Unknown		    = 253,
};

enum class PropertyType : uint8_t {
    Texture     = 0, //Texture
    QValue      = 1, //The "height" of objects, eg walls and platforms 
    IsHidden    = 2, //For floors, whether or not it is hidden or not
    Size        = 3, //Resizable objects such as all platforms, and pillars
    Direction   = 4, //Directional objects such as triplats, boards, ramps etc
    Message     = 5, //String (eg Portal and Board)
    Flip        = 6, //binary geometry option eg pillars stright or dia, or triwalls flip
    FuelType    = 7, //For JetPacks; Whether the jetpack needs fuel or nah
    WinCond     = 8, //Win condition, such as portals and finish marker
    Amount      = 9, //Objects such as crumbs, sheilds, and fuel allow you to choose amount
    TeleID      = 10,   //Teleports connect to eachother
    KeyID       = 11,   //Key to doors
    Speed       = 12,   //Icemen speed
    Strength    = 13,   //Icemen strength
    ChaserStyle = 14,   //Chasers can be saucer, pumpkin, or ghost
    DiamondType = 14,   //Diamonds have different types

    NUM_PROP_TYPES = 15
}; 