class Paml < Formula
  desc "phylogenetic analysis by maximum likelihood"
  homepage "http://abacus.gene.ucl.ac.uk/software/paml.html"
  url "http://abacus.gene.ucl.ac.uk/software/paml4.9e.tgz"
  version "4.9e"
  sha256 "460fabe0c8be9e572e755061abe915449bdc7ee806400119e4f0e1e81234ee8f"
  # doi "10.1093/molbev/msm088"
  # tag "bioinformatics"

  def install
    # Restore permissions, as some are wrong in the tarball archives
    chmod_R "u+rw", "."
    
    cd "src" do
      system "make", "CC=#{ENV.cc}", "CFLAGS=#{ENV.cflags}"
      bin.install %w[baseml basemlg chi2 codeml evolver infinitesites mcmctree pamp yn00]
    end

    pkgshare.install "dat"
    pkgshare.install Dir["*.ctl"]
    doc.install Dir["doc/*"]
    doc.install "examples"
  end

  def caveats
    <<-EOS.undent
      Documentation and examples:
        #{HOMEBREW_PREFIX}/share/doc/paml
      Dat and ctl files:
        #{HOMEBREW_PREFIX}/share/paml
    EOS
  end

  test do
    cp Dir[doc/"examples/DatingSoftBound/*.*"], testpath
    system "#{bin}/infinitesites"
  end
end
