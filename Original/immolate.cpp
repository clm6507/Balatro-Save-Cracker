#include <iostream>
#include "immolate.hpp"

Pack pack_info(std::string pack) {
    if (pack[0] == 'M') {
        return Pack(pack.substr(5), (pack[5] == 'B' || pack[6] == 'p') ? 4 : 5, 2);
    } else if (pack[0] == 'J') {
        return Pack(pack.substr(6), (pack[6] == 'B' || pack[7] == 'p') ? 4 : 5, 1);
    } else {
        return Pack(pack, (pack[0] == 'B' || pack[1] == 'p') ? 2 : 3, 1);
    }
}

int main() {
    int ante = 1;
    std::vector<int> cardsPerAnte = {10,10,10,10,10,10,10,10,10,10};
    std::string output = "";

    std::string seed = "11111111"; 
    std::string deck = "Red Deck";
    std::string stake = "White Stake";
    int version = 10106;
    Instance inst = Instance(seed);
      inst.params = InstParams(deck, stake, false, version);
      inst.initLocks(1, false, false);
      inst.lock("Overstock Plus");
      inst.lock("Liquidation");
      inst.lock("Glow Up");
      inst.lock("Reroll Glut");
      inst.lock("Omen Globe");
      inst.lock("Observatory");
      inst.lock("Nacho Tong");
      inst.lock("Recyclomancy");
      inst.lock("Tarot Tycoon");
      inst.lock("Planet Tycoon");
      inst.lock("Money Tree");
      inst.lock("Antimatter");
      inst.lock("Illusion");
      inst.lock("Petroglyph");
      inst.lock("Retcon");
      inst.lock("Palette");
      inst.setStake(stake);
      inst.setDeck(deck);
      bool ghostDeck = (deck == "Ghost Deck");
      for (int a = 1; a <= ante; a++) {
        inst.initUnlocks(a, false);
        output += "==ANTE " + std::to_string(a) + "==\n";
        output += "Boss: " + inst.nextBoss(a) + "\n";
        std::string voucher = inst.nextVoucher(a);
        output += "Voucher: " + voucher + "\n";
        inst.lock(voucher);
        // Unlock next level voucher
        for (int i = 0; i < VOUCHERS.size(); i+=2) {
            if (VOUCHERS[i] == voucher) {
            };
        };
        output += "Tags: " + inst.nextTag(a) + ", " + inst.nextTag(a) + "\n";

        output += "Shop Queue: \n";
        for (int q = 1; q <= cardsPerAnte[a-1]; q++) {
          output += std::to_string(q) + ") ";
          ShopItem item = inst.nextShopItem(a);
          if (item.type == "Joker") {
            if (item.jokerData.stickers.eternal) output += "Eternal ";
            if (item.jokerData.stickers.perishable) output += "Perishable ";
            if (item.jokerData.stickers.rental) output += "Rental ";
            if (item.jokerData.edition != "No Edition") output += item.jokerData.edition + " ";
          }
          output += item.item + "\n";
        }

        output += "\nPacks: \n";
        int numPacks = (a == 1) ? 4 : 6;
        for (int p = 1; p <= numPacks; p++) {
          std::string pack = inst.nextPack(a);
          output += pack + " - ";
          Pack packInfo = pack_info(pack);
          if (packInfo.type == "Celestial Pack") {
            std::vector<std::string> cards = inst.nextCelestialPack(packInfo.size, a);
            for (int c = 0; c < packInfo.size; c++) {
              output += cards[c];
              output += (c + 1 != packInfo.size) ? ", " : "";
            }
          }
          if (packInfo.type == "Arcana Pack") {
            std::vector<std::string> cards = inst.nextArcanaPack(packInfo.size, a);
            for (int c = 0; c < packInfo.size; c++) {
              output += cards[c];
              output += (c + 1 != packInfo.size) ? ", " : "";
            }
          }
          if (packInfo.type == "Spectral Pack") {
            std::vector<std::string> cards = inst.nextSpectralPack(packInfo.size, a);
            for (int c = 0; c < packInfo.size; c++) {
              output += cards[c];
              output += (c + 1 != packInfo.size) ? ", " : "";
            }
          }
          if (packInfo.type == "Buffoon Pack") {
            std::vector<JokerData> cards = inst.nextBuffoonPack(packInfo.size, a);
            for (int c = 0; c < packInfo.size; c++) {
              JokerData joker = cards[c];
              if (joker.stickers.eternal) output += "Eternal ";
              if (joker.stickers.perishable) output += "Perishable ";
              if (joker.stickers.rental) output += "Rental ";
              if (joker.edition != "No Edition") output += joker.edition + " ";
              output += joker.joker;
              output += (c + 1 != packInfo.size) ? ", " : "";
            }
          }
          if (packInfo.type == "Standard Pack") {
            std::vector<Card> cards = inst.nextStandardPack(packInfo.size, a);
            for (int c = 0; c < packInfo.size; c++) {
              Card card = cards[c];
              if (card.seal != "No Seal") output += card.seal + " ";
              if (card.edition != "No Edition") output += card.edition + " ";
              if (card.enhancement != "No Enhancement") output += card.enhancement + " ";
              char rank = card.base[2];
              if (rank == 'T') output += "10";
              else if (rank == 'J') output += "Jack";
              else if (rank == 'Q') output += "Queen";
              else if (rank == 'K') output += "King";
              else if (rank == 'A') output += "Ace";
              else output += rank;
              output += " of ";
              char suit = card.base[0];
              if (suit == 'C') output += "Clubs";
              else if (suit == 'S') output += "Spades";
              else if (suit == 'D') output += "Diamonds";
              else if (suit == 'H') output += "Hearts";
              output += (c + 1 != packInfo.size) ? ", " : "";
            }
          }
          output += "\n";
        }

        output += "\n";
      };
    std::cout << output << std::endl;
    return 1;
}