class ClustalOmega < Formula
  homepage "http://www.clustal.org/omega/"
  # doi "10.1038/msb.2011.75"
  # tag "bioinformatics"

  url "http://www.clustal.org/omega/clustal-omega-1.2.1.tar.gz"
  sha256 "0ef32727aa25c6ecf732083e668a0f45bc17085c28a5c7b4459f4750419f2b0a"

  depends_on "argtable"

  def install
    system "./configure", "--prefix=#{prefix}",
      "--disable-debug", "--disable-dependency-tracking"
    system "make", "install"
  end

  test do
    system "#{bin}/clustalo", "--version"
  end
end
