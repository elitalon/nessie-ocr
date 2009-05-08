INCLUDES		= -I../include

lib_LTLIBRARIES			= libnessieocr.la
libnessieocr_la_SOURCES	= ClassificationParadigm.cpp \
						  Classifier.cpp \
						  ClassifierStatistics.cpp \
						  Clip.cpp \
						  Dataset.cpp \
						  FeatureExtractor.cpp \
						  FeatureExtractorStatistics.cpp \
						  FeatureVector.cpp \
						  MySqlDataset.cpp \
						  NessieException.cpp \
						  Pattern.cpp \
						  PlainTextDataset.cpp \
						  PostgreSqlDataset.cpp \
						  Preprocessor.cpp \
						  PreprocessorStatistics.cpp \
						  Recognizer.cpp \
						  Region.cpp \
						  Statistics.cpp \
						  Text.cpp

bin_PROGRAMS	= ocrtest
ocrtest_SOURCES	= ocrtest.cpp
ocrtest_LDADD	= libnessieocr.la
noinst_PROGRAMS = ocrtest

