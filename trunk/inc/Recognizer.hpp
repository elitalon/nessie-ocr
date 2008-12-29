/// @file
/// @brief Declaration of the class Recognizer

#if !defined(_RECOGNIZER_H)
#define _RECOGNIZER_H


class Clip;
#include "Text.hpp"
#include "Statistics.hpp"



///
/// Manager of the whole OCR process.
///
/// This class encapsulates all the stages related to the optical character recognition process of
/// every clip within a newspaper's page. For each image provided representing a press clip, you can obtain
/// its text and a number of statistics regarding the recognition process.
///
/// @see Text, Statistics, Clip
///
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2008-12-29
///
class Recognizer
{
public:

    ///
    /// Constructor.
    ///
    /// @author Eliezer Talón (elitalon@gmail.com)
    /// @date 2008-12-29
    ///
    explicit Recognizer ();


    ///
    /// Extracts the text within a single press clip.
    ///
    /// @param pressClip    A Clip object representing the press clip previously loaded.
    ///
    /// @see Clip
    ///
    /// @author Eliezer Talón (elitalon@gmail.com)
    /// @date 2008-12-29
    ///
    void extractText (const Clip& pressClip);


    ///
    /// Returns the text found in a press clip after the recognition process.
    ///
    /// @return A Text object with the data about the text recognized.
    ///
    /// @see Text
    ///
    /// @author Eliezer Talón (elitalon@gmail.com)
    /// @date 2008-12-29
    ///
    const Text& text () const;


    ///
    /// Returns the statistical data regarding the recognition process of a single clip.
    ///
    /// @return An Statistics object with data about the recognition process.
    ///
    /// @see Statistics
    ///
    /// @author Eliezer Talón (elitalon@gmail.com)
    /// @date 2008-12-29
    ///
    const Statistics& statistics () const;


private:

    Text            text_;			///< Text obtained after the recognition process.

    Statistics      statistics_;	///< Statistics gathered during the recognition process.


    // Explicitly disallow compiler-generated functions. DO NOT IMPLEMENT THEM!!
    Recognizer(const Recognizer&);
    Recognizer& operator=(const Recognizer&);
};



inline const Text& Recognizer::text () const
{
    return text_;
};


inline const Statistics& Recognizer::statistics () const
{
    return statistics_;
};


#endif  //_RECOGNIZER_H
