/// @file
/// @brief Declaration of ClassificationParadigm class

#if !defined(_CLASSIFICATION_PARADIGM_H)
#define _CLASSIFICATION_PARADIGM_H


///	@brief		Paradigm to be used by the OCR process to classify the patterns found in a press clip.
/// 
/// @author Eliezer Talón (elitalon@gmail.com)
/// @date 2009-02-17 
class ClassificationParadigm
{
	public:

		///	@brief	Returns the paradigm currently in use.
		///
		///	@return	Identifier of the paradigm.
		const unsigned int& id () const;

		///	@brief	Returns an object set to use the KNN classification paradigm. 
		///
		///	@return A ClassificationParadigm object set to use the KNN paradigm.
		static ClassificationParadigm knn() { return ClassificationParadigm(1); };

		///	@brief	Returns an object set to use the SVM classification paradigm. 
		///
		///	@return A ClassificationParadigm object set to use the SVM paradigm.
		static ClassificationParadigm svm() { return ClassificationParadigm(2); };

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

