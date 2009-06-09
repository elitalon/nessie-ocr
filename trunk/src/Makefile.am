if WITH_MYSQL
MYSQL_SUPPORT = MySqlDataset.cpp
endif

if WITH_POSTGRESQL
POSTGRESQL_SUPPORT	= PostgreSqlDataset.cpp
endif

lib_LTLIBRARIES			= libnessieocr.la
libnessieocr_la_SOURCES	= ClassificationAlgorithm.cpp \
						  Classifier.cpp \
						  ClassifierStatistics.cpp \
						  Dataset.cpp \
						  FeatureExtractor.cpp \
						  FeatureExtractorStatistics.cpp \
						  FeatureVector.cpp \
						  KnnClassificationAlgorithm.cpp \
						  KnnClassifier.cpp \
						  NessieException.cpp \
						  NessieOcr.cpp \
						  Pattern.cpp \
						  PlainTextDataset.cpp \
						  Preprocessor.cpp \
						  PreprocessorStatistics.cpp \
						  Region.cpp \
						  Statistics.cpp \
						  Text.cpp \
						  $(POSTGRESQL_SUPPORT) \
						  $(MYSQL_SUPPORT)


INCLUDES = -I../include/NessieOcr

bin_PROGRAMS	= ocrtest
ocrtest_SOURCES	= ocrtest.cpp
ocrtest_LDADD	= libnessieocr.la
noinst_PROGRAMS = ocrtest

