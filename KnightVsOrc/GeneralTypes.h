#pragma once
#include <string>
#include <iostream>

namespace GeneralTypes {

enum ViewList {TitleScreen,
    Demo,
    DemoExitConfirmBox,
    Fight,
    CreateCustomFight,
    FightConfirmBox,
    SettingsModeWindow,
    WeaponSettings,
    AbilitySettings,
    CharacterSettings
};

// X-MACRO to generate an enum which can be printed as a string (operator overload)
// Following is like defining  "enum ModifierType { Add, Mult, PercentInc}"
#define MODIFIERTYPE   \
X(Add)                 \
X(Mult)                \
X(PercentInc)


enum ModifierType {
#   define X(a) a,
    MODIFIERTYPE
#   undef X
    ModifierTypeCount
};

char const* const modifierType_str[] = {
#   define X(a) #a,
    MODIFIERTYPE
#   undef X
    0
};



// X-MACRO to generate an enum which can be printed as a string (operator overload)
// Following is like defining  "enum Class {Char, Knight, Orc};"
#define CLASS   \
X(Custom)       \
X(Knight)       \
X(Orc)


    enum Class {
#   define X(a) a,
        CLASS
#   undef X
        ClassCount
    };

    char const* const class_str[] = {
    #   define X(a) #a,
        CLASS
    #   undef X
        0
    };

// X-MACRO to generate an enum which can be printed as a string (operator overload)
// Following is like defining  "enum Status { NoStatus, stun };"
#define STATUS \
X(NoStatus)    \
X(Stunned)     \
X(Buff)

    enum Status {
#   define X(a) a,
        STATUS
#   undef X
        StatusCount
    };

    char const* const status_str[] = {
    #   define X(a) #a,
        STATUS
    #   undef X
        0
    };

// X-MACRO to generate an enum which can be printed as a string (operator overload)
// Following is like defining  "enum WeaponType {Fist, Sword, Axe};"
#define WEAPONTYPE  \
X(Fist)             \
X(Sword)            \
X(Axe)

    enum WeaponType {
#   define X(a) a,
        WEAPONTYPE
#   undef X
        WeaponTypeCount
    };

    char const* const weaponType_str[] = {
    #   define X(a) #a,
        WEAPONTYPE
    #   undef X
        0
    };

    inline std::ostream& operator<<(std::ostream& os, enum GeneralTypes::Class c)
    {
        if (c >= ClassCount || c < 0) return os << "???";
        return os << class_str[c];
    }

    inline bool operator==(std::string s, enum GeneralTypes::Class c) {
        return (s == class_str[c]);
    }

    inline std::ostream& operator<<(std::ostream& os, enum GeneralTypes::Status s)
    {
        if (s >= StatusCount || s < 0) return os << "???";
        return os << status_str[s];
    }

    inline std::ostream& operator<<(std::ostream& os, enum GeneralTypes::WeaponType wt)
    {
        if (wt >= WeaponTypeCount || wt < 0) return os << "???";
        return os << weaponType_str[wt];
    }

    inline std::ostream& operator<<(std::ostream& os, enum GeneralTypes::ModifierType mt)
    {
        if (mt >= ModifierTypeCount || mt < 0) return os << "???";
        return os << modifierType_str[mt];
    }

    inline const char* const BoolToString(bool b)
    {
        return b ? "true" : "false";
    }
};