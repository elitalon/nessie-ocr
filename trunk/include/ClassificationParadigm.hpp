/// @file
/// @brief Declaration of ClassificationParadigm class

#if !defined(_CLASSIFICATION_PARADIGM_H)
#define _CLASSIFICATION_PARADIGM_H


///	@brief		Paradigm used by the OCR process in the classification stage.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-17 
class ClassificationParadigm
{
	public:

		///	@brief	Get the paradigm currently in use.
		///
		///	@return	Identifier of the paradigm.
		const unsigned int& id () const;

		///	@brief	Get the KNN classification paradigm.
		///
		///	@return A ClassificationParadigm object set to the KNN classification paradigm.
		static ClassificationParadigm knn() { return ClassificationParadigm(1); };

	private:

		unsigned int	id_;	///< Internal identifier of the paradigm.

		///	@brief	Private constructor that prevents creation of new paradigms.
		///
		///	@param	id	Identifier of the paradigm.
		explicit ClassificationParadigm (const unsigned int& id);
};

inline const unsigned int& ClassificationParadigm::id () const
{
	return id_;
};

#endif

