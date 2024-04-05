#ifndef __PFADFINDUNG_HPP
#define __PFADFINDUNG_HPP

#include <cmath>
#include <memory>
#include <vector>

namespace stemaj {

struct Knoten {
    int x, y; // Koordinaten des Knotens
    double g, h; // g: Kosten vom Startknoten zum aktuellen Knoten, h: Heuristik (geschätzte Kosten vom aktuellen Knoten zum Ziel)
    std::shared_ptr<Knoten> eltern; // Smart-Zeiger auf den übergeordneten Knoten

    Knoten(int _x, int _y, double _g, double _h, std::shared_ptr<Knoten> _eltern = nullptr) : x(_x), y(_y), g(_g), h(_h), eltern(_eltern) {}

    double f() const {
        return g + h; // Gesamtschätzkosten des Pfads durch den aktuellen Knoten
    }
};

class Pfadfindung
{
  public:
    Pfadfindung(const std::vector<std::vector<int>>& _gitter);
    virtual ~Pfadfindung() = default;

    std::vector<std::pair<int, int>> FindePfad(int start_x, int start_y, int ziel_x, int ziel_y);

  private:

  private:
    double heuristik(int x1, int y1, int x2, int y2) {
        return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)); // Euklidische Distanz
    }

    void findeNaechstenGueltigenPunkt(int x, int y, bool istStartpunkt, int& gueltiger_x, int& gueltiger_y);
     std::shared_ptr<Knoten> findeNiedrigstenF(const std::vector<std::shared_ptr<Knoten>>& liste);
std::shared_ptr<Knoten> findeKnotenInListe(const std::vector<std::shared_ptr<Knoten>>& nodeList, int x, int y);
 bool istKnotenInListe(const std::vector<std::shared_ptr<Knoten>>& nodeList, int x, int y);
   std::vector<std::pair<int, int>> konstruierePfad(const std::shared_ptr<Knoten>& zielknoten);

    int clamp(int val, int min_val, int max_val) {
        return std::max(min_val, std::min(val, max_val));
    }
    std::vector<std::vector<int>> gitter; // 2D-Gitter, das die Karte repräsentiert
    int breite, hoehe; // Abmessungen des Gitters

     
     std::vector<std::shared_ptr<Knoten>> offeneListe;
    std::vector<std::shared_ptr<Knoten>> geschlosseneListe;

};

} // namespace stemaj

#endif //__PFADFINDUNG_HPP