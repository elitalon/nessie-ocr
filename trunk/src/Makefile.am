lib_LTLIBRARIES			= libnessieocr.la
libnessieocr_la_SOURCES	= ClassificationAlgorithm.cpp \
						  Classifier.cpp \
						  ClassifierStatistics.cpp \
						  Clip.cpp \
						  Dataset.cpp \
						  FeatureExtractor.cpp \
						  FeatureExtractorStatistics.cpp \
						  FeatureVector.cpp \
						  KnnClassificationAlgorithm.cpp \
						  KnnClassifier.cpp \
						  MySqlDataset.cpp \
						  NessieException.cpp \
						  NessieOcr.cpp \
						  Pattern.cpp \
						  PlainTextDataset.cpp \
						  PostgreSqlDataset.cpp \
						  Preprocessor.cpp \
						  PreprocessorStatistics.cpp \
						  Region.cpp \
						  Statistics.cpp \
						  Text.cpp

INCLUDES = -I../include/NessieOcr

bin_PROGRAMS	= ocrtest
ocrtest_SOURCES	= ocrtest.cpp
ocrtest_LDADD	= libnessieocr.la
noinst_PROGRAMS = ocrtest

