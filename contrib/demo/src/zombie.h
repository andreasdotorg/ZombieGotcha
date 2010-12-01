#ifndef ZOMBIEH
#define ZOMBIEH

//! Radio Toy
void zombiegotcha();

//! The type of a zombie tech.
typedef enum {
  HUMAN, ZOMBIE, NINJA, PIRATE,
  GOODSPEED
} PetType;

//! The gender of a pet.
typedef enum {
  MALE, FEMALE
} PetGender;

//! Zombie Character
typedef struct {
  PetType type;
  PetGender gender; // 0 male, 1 female
  __xdata u8* sprite;
  u16 x;
  u16 y;
  u8 frame;
  u8 health;
  u8 drawable;
  char name[8];
} Pet;

//! The player's own pet.
extern Pet localpet;
//! The remote pet.
extern Pet remotepet;

//! Initialize a Pet structure.
void zombieinit(Pet *pet);
//! Create and Introduce a Zombie
void zombiecreate(Pet *pet);
//Draw the local and remote sprites.
void zombiedraw();

#endif
