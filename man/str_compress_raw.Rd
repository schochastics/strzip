% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/strzip.R
\name{str_compress_raw}
\alias{str_compress_raw}
\title{Compress a string using SMAZ algorithm}
\usage{
str_compress_raw(x)
}
\arguments{
\item{x}{A character vector string to compress.}
}
\value{
A list of raw vectors containing the compressed data.
}
\description{
Compress a string using SMAZ algorithm
}
\examples{
str_compress_raw(c("Hello", "world", "smaz"))
}
