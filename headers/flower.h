/// \file  flower.h
/// \brief Declaration of the Flower class.

#ifndef FLOWER_H
#define FLOWER_H

#include <string>
#include <vector>

using namespace std;

/// \brief The Flower class contains information about a flower (name, color, scent intensity, and habitat regions).
class Flower {
public:
    /// \name Constructors
    /// @{
    /// \brief Default constructor.
    Flower() = default;
    Flower(string name, string color, string smell, vector<string> regions);
    /// \brief Copy constructor.
    Flower(const Flower& other) = default;
    /// \brief Move constructor.
    Flower(Flower&& other) = default;
    /// \brief Destructor.
    ~Flower() = default;
    /// @}

    /// \name Getters
    /// @{
    string GetName() const { return name_; }
    string GetColor() const { return color_; }
    string GetSmell() const { return smell_; }
    vector<string> GetRegions() const { return regions_; }
    /// @}

    /// \name Setters
    /// @{
    void SetName(string name) { name_ = name; }
    void SetColor(string color) { color_ = color; }
    void SetSmell(string smell) { smell_ = smell; }
    void SetRegions(vector<string> regions) { regions_ = regions; }
    /// @}

    /// \name Operator Overloading
    /// \details Comparison based on key fields (name, color, smell).
    /// @{
    bool operator>(const Flower& other) const;
    bool operator<(const Flower& other) const;
    bool operator>=(const Flower& other) const;
    bool operator<=(const Flower& other) const;
    bool operator==(const Flower& other) const;
    Flower& operator=(const Flower& other);
    /// @}

    /// \brief Compares the current object with another based on key fields.
    /// \param other Reference to another Flower object.
    /// \return true if name, color, and smell match; otherwise false.
    /// \details
    /// Two objects are considered "equal" if their name, color, and smell fields
    /// are the same. The regions field is ignored in this comparison.
    bool EqFlowers(const Flower& other) const;

private:
    string name_;   ///< Name of the flower.
    string color_;  ///< Color of the flower.
    string smell_;  ///< Scent intensity ("strong", "moderate", "weak").
    vector<string> regions_;  ///< Regions where the flower is found.
};

#endif