char *PerlScriptName[]={"rec_sum.pl","count.pl","p\
rocess_list.pl","make_license.pl","CCsed.script","\
msa2bootstrap.pl","t_coffee_dpa","t_coffee_dpa2","\
tc_generic_method.pl","generic_method.tc_method","\
clustalw_method.tc_method","extract_from_pdb","ins\
tall.pl","clean_cache.pl","nature_protocol.pl","mo\
cca","dalilite.pl","wublast.pl","blastpgp.pl","ncb\
iblast_lwp.pl","wublast_lwp.pl","RNAplfold2tclib.p\
l","fasta_seq2RNAplfold_templatefile.pl","fasta_se\
q2hmmtop_fasta.pl","fasta_seq2consan_aln.pl","clus\
talw_aln2fasta_aln.pl","msf_aln2fasta_aln.pl","bla\
st_aln2fasta_aln.pl","blast_xml2fasta_aln.pl","fas\
ta_aln2fasta_aln_unique_name.pl","newick2name_list\
.pl","excel2fasta.pl","any_file2unix_file.pl","End\
List"};char *PerlScriptFile[]={"use File::Copy;\nu\
se Env qw(HOST);\nuse Env qw(HOME);\nuse Env qw(US\
ER);\n$x_field=0;\n$y_field=1;\n$y_field_set=1;\n$\
nyf=1;\n\n$interval=0;\n$file=\"stdin\";\n\n$print\
_avg=1;\n$print_sd=0;\n$print_sum=0;\n$print_n=0;\\
nforeach $value ( @ARGV)\n    {\n	if ($value ne $A\
RGV[$np]) \n	    {\n	    ;\n	    }\n	elsif($value \
eq \"-print_all\")\n	    {\n	    $print_sd=$print_\
avg=$print_n=$print_sum=1;\n	    $np++;\n	    }\n	\
elsif($value eq \"-print_sum\")\n	    {\n	    $pri\
nt_sum=1;\n	    $print_avg=0;\n	    $np++;\n	    }\
\n	elsif($value eq \"-print_n\")\n	    {\n	    $pr\
int_n=1;\n	    $print_avg=0;\n	    $np++;\n	    }\\
n	elsif($value eq \"-print_avg\")\n	    {\n	    $p\
rint_avg=1;\n	    $print_avg=0;\n	    $np++;\n	   \
 }\n	elsif($value eq \"-sd\")\n	    {\n	    $print\
_sd=1;\n	    $print_avg=0;\n	    $np++;\n	    }\n	\
elsif($value eq \"-h\")\n	    {\n	    $header=1;\n\
	    $np++;\n	    }\n	elsif ($value eq \"-i\")\n	 \
   {\n	    $interval= $ARGV[++$np];\n	    $np++;\n\
    	    }\n	elsif ($value eq \"-r\")\n	    {\n	  \
  $min= $ARGV[++$np];\n	    $max= $ARGV[++$np];\n	\
    $np++;\n    	    }\n	\n	elsif ($value eq \"-x\\
")\n	    {\n	    $x_field= $ARGV[++$np]-1;\n	    $\
np++;\n    	    }\n	elsif ($value eq \"-y\")\n	   \
 {\n	    $nyf=0;  \n	    while ($ARGV[$np+1] && !(\
$ARGV[$np+1]=~/\\-/))\n	      {\n		$y_field[$nyf++\
]=$ARGV[++$np]-1;\n		$y_field_set=1;\n	      }\n\n\
	    $np++;\n    	    }\n	elsif ($value eq \"-file\
\")\n	    {\n	    $file= $ARGV[++$np];\n	    $file\
_set=1;\n	    $np++;\n    	    }       \n	elsif ( \
$value eq \"h\" ||  $value eq \"-h\" || $value eq \
\"-H\" || $value eq \"-help\" || $value eq \"help\\
")\n	  {\n	    print STDOUT \"data_analyse: Analys\
e and discretization of data\\n\";\n	    print STD\
OUT \"       -file:    <file containing the data t\
o analyze>,.<def=STDIN>\\n\";\n	    print STDOUT \\
"       -x: <field containing the X>,.............\
..<Def=0>\\n\";\n	    print STDOUT \"       -y: <f\
ield containing the Y>,...............<Def=1>\\n\"\
;\n	    print STDOUT \"       -i:<Interval size on\
 the X>,...............<Def=0>\\n\";\n	    print S\
TDOUT \"       -i:<0:only one interval>\\n\";\n	  \
  print STDOUT \"       -r:<Range of the X>\\n\";\\
n	    print STDOUT \"       -sd: print standard de\
viation on the Y\";\n	    print STDOUT \"       -h\
  : print column header \\n\";\n	    exit (0);\n	 \
 }\n	elsif ($value=~/-/)\n	  {\n	    print \"$valu\
e is not a valid FLAG[FATAL]\\n\";\n	    exit (0);\
\n	   } \n	elsif ($list eq \"\") \n	    {\n	    $f\
ile=$ARGV[$np];\n	    $np++;\n	    }\n	\n	\n      \
}\n\n\n\n\n\nif ($file eq \"stdin\")\n	{\n	$remove\
_file=1;\n	$file=\"tmp$$\";\n	open (F, \">$file\")\
;\n	while (<STDIN>)\n		{\n		print F $_;\n		}\n	clo\
se (F);\n	 \n	;}\n\n\n\n\nif ($interval && $max)\n\
  {\n    $interval_size=($max-$min)/$interval;\n  \
}\nelsif ($interval)\n  {\n    open(F,$file);  \n \
   my $set_max=0;\n    my $set_min=0;\n    while (\
<F>)\n      {\n	my $v=$_;\n	chomp($v);\n	print \"-\
-$v--\";\n	\n	if ($v<$min ||!$set_min){$set_min=1;\
$min=$v;}\n	if ($v>$max ||!$set_max){$set_max=1;$m\
ax=$v;}\n      }\n    close (F);\n    print \"$min\
 $max uuuu\";\n    $interval_size=($max-$min)/$int\
erval;\n  }\nopen(F,$file);  \nwhile (<F>)\n  {\n \
   $line=$_;\n    if (!/\\S/){next;}\n    @list=($\
line=~/(\\S+)/g);\n    \n    if ($interval==0){$bi\
n=0;}\n    else{$bin=int (($list[$x_field]-$min)/(\
$interval_size));}\n\n    \n    if ($bin && $bin==\
$interval){$bin--;}\n    for ( $a=0; $a<$nyf; $a++\
)\n      {\n	$sum{$a}{$bin}+=$list[$y_field[$a]];\\
n	$sum2{$a}{$bin}+=$list[$y_field[$a]]*$list[$y_fi\
eld[$a]];\n	$n{$a}{$bin}++;\n      }\n  }\n\nif (!\
$interval){$interval=1;}\nfor ( $a=0; $a<$interval\
; $a++)\n  {\n    printf ( \"%4d %4d \", $interval\
_size*$a, $interval_size*($a+1));\n    for ( $b=0;\
 $b<$nyf; $b++)	\n      {\n	$i=$interval*$a;\n	if \
( $n{$b}{$a}==0)\n	  {\n	    $avg=0;\n	    $sd=0;\\
n	  }\n	else\n	  {\n	    $avg=$sum{$b}{$a}/$n{$b}{\
$a};\n	    $sd=sqrt($sum2{$b}{$a}*$n{$b}{$a}-$sum{\
$b}{$a}*$sum{$b}{$a})/($n{$b}{$a}*$n{$b}{$a});\n	 \
 }\n	if ($print_n) {printf \"%15.4f \", $n{$b}{$a}\
;}\n	if ($print_sum){printf \"%15.4f \", $sum{$b}{\
$a};}\n	if ($print_avg){printf \"%15.4f \", $avg}\\
n	if ($print_sd) {printf \"%15.4f \", $sd;}\n     \
 }\n    printf (\"\\n\");\n  }\n\n\nif ( $remove_f\
ile){unlink $file;}\n","use File::Copy;\nuse Env q\
w(HOST);\nuse Env qw(HOME);\nuse Env qw(USER);\n\n\
foreach $v (@ARGV){$cl.=$v;}\n\n\nif ( $cl=~/-k(\\\
d+)/){$k=$1;}\nelse {$k=1;}\nif ( $cl=~/-w(\\d+)/)\
{$w=$1;}\nelse {$w=-1;}\nif ( $cl=~/-p(\\d+)/){$p=\
$1;}\nelse {$p=-1;}\n\nwhile (<STDIN>)\n  {\n    @\
l=($_=~/(\\S+)/g);\n    $v=$l[$k-1];\n    if ( !$h\
{$v}){@ll=($v, @ll);}\n    \n    if ( $w==-1)\n   \
   {$h{$v}++;}\n    else\n      {$h{$v}+=$l[$w-1];\
}\n\n    if ($p!=-1){$print{$v}=$l[$p-1];}\n\n  }\\
nforeach $v (@ll)\n  {\n    print \"$v $print{$v} \
$h{$v}\\n\";\n  }\n","\nuse Env qw(HOST);\nuse Env\
 qw(HOME);\nuse Env qw(USER);\n$random_tag=int (ra\
nd 10000)+1;\n$unique_prefix=\"$$.$HOST.$random_ta\
g\";\n$queue=\"distillery.and.mid\";\n$monitor=0;\\
n$stderr_file=\"/dev/null\";\n$stdio_file=\"/dev/n\
ull\";\n$log_file=\"/dev/null\";\n$pause_time=0;\n\
$max_sub_jobs=60;\n$min_sub_jobs=30;\n$output_all=\
0;\n$var='\\$';\n\nforeach $value ( @ARGV)\n    {\\
n	if ($value ne $ARGV[$np]) \n	    {\n	    ;\n	   \
 }\n	elsif ($value eq \"-max_sub_jobs\")\n	    {\n\
	    $max_sub_jobs= $ARGV[++$np];\n	    $np++;\n  \
  	    }	\n	elsif ($value eq \"-min_sub_jobs\" )\n\
	    {\n	    $min_sub_jobs= $ARGV[++$np];\n	    $n\
p++;\n    	    }\n	elsif ($value eq \"-para\")\n	 \
   {\n	    $para=1;\n	    $monitor=1;\n	    $np++;\
\n    	    }\n	elsif ($value eq \"-monitor\") \n	 \
   {\n	    $monitor=1;\n	    $np++;\n	    }\n	elsi\
f ($value eq \"-no_monitor\") \n	    {\n	    $moni\
tor=0;\n	    $np++;\n	    }\n	elsif ($value eq \"-\
queue\")\n	    {\n	    $queue=$ARGV[++$np];\n	    \
$np++;\n	    }	\n	elsif ($value eq \"-stderr_file\\
")\n	    {\n	    $stderr_file=$ARGV[++$np];\n	    \
$np++;\n	    }\n	elsif ($value eq \"-stdio_file\")\
\n	    {\n	    $stdio_file=$ARGV[++$np];\n	    $np\
++;\n	    }\n	elsif ($value eq \"-output_all\")\n	\
    {\n	    $output_all=1;\n	    $np++;\n	    }\n	\
elsif ($value eq \"-pause\") \n	    {\n	    $pause\
_time=$ARGV[++$np];\n	    $np++;\n	    }\n	elsif (\
$value eq \"-log\")\n	      {\n	       $log=1;\n	 \
      \n	       if ($ARGV[$np+1]=~/\\-\\S+/) \n	  \
        {\n		  $log_file=\"stderr\";\n	          }\
\n	       else \n	          {\n		  $log_file=$ARGV\
[++$np]; \n		  ++$np;\n		 \n	          }\n	      }\
\n	elsif ( $value eq \"-com\")\n	    {\n		\n		if (\
!$ARGV[$np+1]=~/^\\'/) { $com=$ARGV[++$np];}\n		el\
se {$com=$ARGV[++$np];}\n\n	     $np++;\n	    }\n	\
elsif ( $value eq \"-check\")\n	  {\n	    \n	    i\
f (!$ARGV[$np+1]=~/^\\'/) { $check=$ARGV[++$np];}\\
n	    else {$check=$ARGV[++$np];}\n	    $np++;\n	 \
 }\n	elsif ($com eq \"\") \n	    {\n	    $com_set=\
1;\n	    $com=$ARGV[$np];\n	    \n	    $np++;\n	  \
  }\n	elsif ($list eq \"\") \n	    {\n	    $list_s\
et=1;\n	    $list=$ARGV[$np];\n	    $np++;\n	    }\
\n	elsif ( $var_set eq \"\")\n	    {\n	    $var_se\
t=1;\n	    $var=$ARGV[$np];\n	    $np++;\n	    }\n\
	}\n\n\n\n\nif ( $com eq \"\"){print \"You Need to\
 Provide a Command [FATAL]\\n\";\n	      die;\n	  \
   }\n\n\n\nif ($list_set==0) \n    {\n    $x= int\
 (rand 100000)+1;\n    $tmp_file_name=\"tmp_file_$\
x\";\n    open ( TMP, \">$tmp_file_name\");\n    w\
hile (<STDIN>)\n      {\n	print TMP $_;\n      }\n\
    close (TMP);\n    open (F, $tmp_file_name);\n \
   }\nelse \n    {\n    open (F, $list);\n    }\n\\
nif ($para==0) \n    {\n\n     @tc_list= <F>;\n   \
  close (F); \n     \n     foreach $val(@tc_list) \
\n	    {\n	      \n	      \n	      \n	      $loc_c\
om=$com;\n	      if ($check){$loc_check=$check;}\n\
	      \n	      @i_val=($val=~/([^\\s]+)/g);\n	   \
   \n	      if ( $#i_val==0)\n		{\n		  if ($check)\
{$loc_check=~s/$var/$i_val[0]/g;}\n		  $loc_com=~s\
/$var/$i_val[0]/g;\n		}\n	      else\n		{\n		  for\
 ($n=1; $n<=$#i_val+1;$n++ )\n		    {\n		      \n	\
	      $sub=\"$var$n\";\n		      \n		      $loc_co\
m=~s/$sub/$i_val[$n-1]/g;\n		      if ($check){$lo\
c_check=~s/$var/$i_val[0]/g;}\n		    }\n		}\n	    \
  if ( $check && -e $loc_check)\n		{\n		  print ST\
DERR \"skipping $loc_com...\\n\";\n		  }\n	      e\
lse\n		{\n		  system \"$loc_com\";\n		}\n	    }\n \
   exit;\n    }\n\nelsif ($para==1) \n    {\n    p\
rint STDERR \"do parallel execution of: \\\"$com $\
list\\\"\\n\";\n    \n    if ($log==1) \n	{\n	if (\
$log_file eq \"stdout\" || $log_file eq \"stderr\"\
 ) \n		{\n		$log_file=\"\";\n	        }\n\n       \
 else \n		{\n		system \"echo LOG FILE> $log_file\"\
;\n		\n	        }\n	}\n    else	\n	{\n	open ( OUT,\
 \">/dev/null\");\n	}\n	\n    \n    $id=0;\n    $n\
_sub=0;\n    while ($val=<F>) \n	    {	    	    \n\
	    $job_log[$id]=\"$HOME/tmp/$unique_prefix.$id.\
log_file\";\n	    \n	    $job=$unique_prefix.\"_$i\
d\";\n	    open (JOB, \">$job\");\n	    \n	    $lo\
c_com=$com;\n	    chop $val;\n\n	    $loc_com=~s/\\
\$/$val/g;\n	 \n	    print JOB \"#!/bin/csh\\n\";\\
n	    print JOB \"#\\$ -cwd\\n\";\n	    print JOB \
\"#\\$ -N $unique_prefix\\n\";\n	    if ($queue &&\
 !($queue eq \" \")) {print JOB \"#\\$ -l $queue\\\
n\";}\n	    print JOB \"#\\n\";	    \n            \
print JOB \"$loc_com\\n\";\n	    print JOB \"echo \
FINISHED  >> $job_log[$id]\\n\";\n	    print JOB \\
"pwd\\n\";\n	    \n	    close (JOB);\n	    if ( $o\
utput_all==1)\n		{\n		system \"qsub $job >  $uniqu\
e_prefix\";		\n	        }\n	    else\n		{system \"\
qsub $job -e $stderr_file -o $stdio_file >$unique_\
prefix\";	        \n	        } \n\n\n\n	    print \
STDERR \"$id: $output_all\\n\";\n	    $n_sub++;\n	\
    if ( $max_sub_jobs && $n_sub==$max_sub_jobs) \\
n		{\n		$n_sub=monitor_process($min_sub_jobs,@job_\
log); 		 \n		\n	        }	\n	   \n            unli\
nk $unique_prefix;\n	    sleep $pause_time;\n	    \
$id++;\n	    }\n\n    close (OUT);\n    close (F);\
\n\n    print STDERR \"Your $id Jobs Have Been Sub\
mited (NAME=$unique_prefix)\\n\";\n    monitor_pro\
cess (0, @job_log);\n    foreach $file(@job_log) {\
if (-e $file) {unlink($file);}}\n    \n    }\n\nsu\
b monitor_process ( @job_list)\n    {\n    my (@jo\
b_list)=@_;\n    my $min_sub_jobs=shift (@job_list\
);\n    my $n_sub_jobs;\n    my $finished;\n    my\
 $n=0;\n\n    $n_sub_jobs=-1;\n    $finished=0;\n \
   print STDERR \"\\nMonitor Batch: [$min_sub_jobs\
]\";\n       \n    while (!$finished && (($n_sub_j\
obs>$min_sub_jobs)|| $n_sub_jobs==-1) ) \n	{\n	$fi\
nished=1;\n	$n_sub_jobs=0;\n	$n=0;\n	foreach $file\
 (@job_list)\n	        {\n	\n		if (-e $file){;}\n	\
	else \n		    {\n		    $finished=0; $n_sub_jobs++;\
\n	            }\n	        }\n	system \"sleep 1\";\
\n        }\n    \n    return $n_sub_jobs;\n    }\\
n    \n    \nif ($tmp_file_name){unlink($tmp_file_\
name);}\n","\n\nforeach ($np=0; $np<=$#ARGV; $np++\
)\n    {\n    $value=$ARGV[$np];\n\n    if ($value\
 eq \"-file\")\n      {\n      $file= $ARGV[++$np]\
;\n      }\n    elsif ($value eq \"-type\")\n     \
 {\n        $type= $ARGV[++$np];\n      }\n    els\
if ($value eq \"-institute\")\n      {\n        $i\
nstitute= $ARGV[++$np];\n      }\n    elsif ($valu\
e eq \"-author\")\n      {\n        $author= $ARGV\
[++$np];\n      }\n    elsif ($value eq \"-date\")\
\n      {\n        $date= $ARGV[++$np];\n      }\n\
     elsif ($value eq \"-program\")\n      {\n    \
    $program= $ARGV[++$np];\n      }\n    elsif ($\
value eq \"-email\")\n      {\n        $email= $AR\
GV[++$np];\n      }\n    else\n      {\n	print \"$\
value is an unkown argument[FATAL]\\n\";\n	exit (1\
);\n      }\n  }\n\n\n\nopen F, $file || die;\npri\
nt $INSTITUTE;\nif ( $type eq \"c\"){print \"/****\
**************************COPYRIGHT NOTICE********\
***********************/\\n\";}\nif ( $type eq \"p\
erl\"){print \"##############################COPYR\
IGHT NOTICE##############################/\\n\";}\\
nif ( $type eq \"txt\"){print \"------------------\
-------------COPYRIGHT NOTICE---------------------\
---------/\\n\";}\n\n\nwhile (<F>)\n  {\n  s/\\$IN\
STITUTE/$institute/g;\n  s/\\$AUTHOR/$author/g;\n \
 s/\\$DATE/$date/g;\n  s/\\$PROGRAM/$program/g;  \\
n  s/\\$EMAIL/$email/g;  \n  if ( $type eq \"txt\"\
){print $_;}\n  elsif ($type eq \"c\"){chop $_; pr\
int \"\\/*$_*\\/\\n\";}\n  elsif ($type eq \"perl\\
"){print \"\\#$_\";}\n}\nclose (F);\nif ( $type eq\
 \"c\"){print \"/******************************COP\
YRIGHT NOTICE*******************************/\\n\"\
;}\nif ( $type eq \"perl\"){print \"##############\
################COPYRIGHT NOTICE##################\
############/\\n\";}\nif ( $type eq \"txt\"){print\
 \"-------------------------------COPYRIGHT NOTICE\
------------------------------/\\n\";}\n\n","\nwhi\
le (<>)	\n	{\n	s/\\=cc/123456789/g;\n	s/\\bcc/\\$\\
\(CC\\)/g;\n	s/123456789/\\=cc/g;\n	print $_;\n	}\\
n\n","$version=\"1.00\";\n$rseed= int(rand(100000)\
)+1;\n\n\nif ( $#ARGV==-1)\n  {\n    print \"msa2b\
ootstrap -i <input_file> -input <seq|msa|matrix|tr\
ee> -n <N-Boostrap> -o <outtree> -tmode <nj|upgma|\
parsimony|ml> -dmode <kimura> -alignpg <t_coffee |\
 muscle | clustalw> -rtree <file> -stype <prot|cdn\
a|dna> -recompute -system <cygwin|unix>\";\n    pr\
int \"\\n\\t-i: input file, can be sequneces, msa,\
 matrix, trees, type is specified via -input\";\n \
   print \"\\n\\t-input: Type of input data\";\n  \
  print \"\\n\\t\\tmsa: msa in fasta format\";\n  \
  print \"\\n\\t\\tseq: compute an msa with -align\
pg\";\n    print \"\\n\\t\\tmatrix: phylipp distan\
ce matrix fed directly to method -tmode [caveat: t\
mode=nj or upgma]\";\n    print \"\\n\\t\\ttree: l\
ist of newick trees directly fed to consence in or\
der to generate a bootstraped tree\";\n    \n    p\
rint \"\\n\\t-n: number of bootstrap replicates\";\
\n    print \"\\n\\t-o: name of the output tree. F\
iles are not overwritten. Use -recompute to overwr\
ite existing file\";\n    print \"\\n\\t-tmode: tr\
ee mode: nj|upgma|parsimony|ml\";\n    print \"\\n\
\\t-dmode: distance mode\";\n    print \"\\n\\t-al\
ignpg: program for aligning sequences (t_coffee=de\
fault)\";\n    print \"\\n\\t-rtree: replicate tre\
e file (default: no file)\";\n    print \"\\n\\t-r\
msa: replicate msa file (default: no file)\";\n   \
 print \"\\n\\t-rmat: replicate matrix file (defau\
lt: no file)\";\n    print \"\\n\\t-stype: sequenc\
e type: protein, dna or cdna\";\n    print \"\\n\\\
t-recompute: force files to be overwritten\";\n   \
 print \"\\n\\t-system: cygwin|unix\";\n      \n\n\
    \n    &my_exit (EXIT_FAILURE);\n  }\nforeach $\
arg (@ARGV){$command.=\"$arg \";}\n\nprint \"CLINE\
: $command\\n\";\n$threshold=100;\n$trim_msa=0;\n$\
stype=\"prot\";\nprint \"msa2bootstrap \";\n\n$sys\
tem=\"cygwin\";\nif(($command=~/\\-system (\\S+)/)\
)\n  {\n    $system=$1;\n    if ( $system eq \"cyg\
win\")\n      {\n	$exec_extension=\".exe\";\n     \
 }\n    elsif ( $system eq \"unix\")\n      {\n	$e\
xec_extension=\"\";\n	print \"system=Unix\";die;\n\
      }\n    else\n      {\n	print \"msa2boostrap:\
 -system=$system is an unknown mode [FATAL]\\n\"; \
die;\n      }\n    \n    print \"-system $system \\
";\n  }\nif(($command=~/\\-stype (\\S+)/))\n  {\n \
   $stype=$1;\n  }\nprint \"-stype=$stype \";\n\n\\
n\nif(($command=~/\\-i (\\S+)/))\n  {\n    $msa=$1\
;\n    print \"-i $msa \";\n  }\n\nif(($command=~/\
\\-rtree (\\S+)/))\n  {\n    $rtree=$1;\n    print\
 \"-rtree=$rtree \";\n  }\n\nif(($command=~/\\-rms\
a (\\S+)/))\n  {\n    $rmsa=$1;\n  }\nif(($command\
=~/\\-rmat (\\S+)/))\n  {\n    $rmat=$1;\n  }\n$in\
put=\"seq\";\nif(($command=~/\\-input (\\S+)/))\n \
 {\n    $input=$1;\n  }\nprint \"-input=$input \";\
\n\n$dmode=\"kimura\";\nif(($command=~/\\-dmode (\\
\S+)/))\n  {\n    $dmode=$1;\n  }\nprint \"-dmode=\
$dmode \";\n$alignpg=\"muscle\";\nif(($command=~/\\
\-alignpg (\\S+)/))\n  {\n    $alignpg=$1;\n  }\np\
rint \"-alignpg=$dmode \";\n\n$tmode=\"nj\";\nif((\
$command=~/\\-tmode (\\S+)/))\n  {\n    $tmode=$1;\
\n  }\nprint \"-tmode=$tmode \";\n$recompute=0;\ni\
f(($command=~/\\-recompute/))\n  {\n    $recompute\
=1;\n    print \"-recompute \";\n  }\n\n$out=$msa;\
\n$out=~s/\\..*//;\n$out.=\".bph\";\nif(($command=\
~/\\-o (\\S+)/))\n  {\n    $out=$1;\n    \n  }\npr\
int \"-out=$out \";\nif (-e $out && !$recompute)\n\
  {\n    print \"\\nNo Computation Required $out a\
lready exists\\n\";\n    &my_exit (EXIT_SUCCESS);\\
n    \n  }\n\n$n=100;\nif(($command=~/\\-n (\\d+)/\
))\n  {\n    $n=$1;\n  }\nprint \"-n=$n \";\n$seed\
=3;\nif(($command=~/\\-s (\\d+)/))\n  {\n    $seed\
=$1;\n  }\nprint \"-s=$seed \";\n\nif(($command=~/\
\\-run_name (\\d+)/))\n  {\n    $suffix=$1;\n  }\n\
else\n  {\n    $msa=~/([^.]+)/;\n    $suffix=$1;\n\
  }\nprint \"-run_name=$suffix\\n\";\n\n\nif ( $in\
put eq \"seq\")\n  {\n    $seq=$msa;\n    $msa=\"$\
suffix.prot_msa\";\n    \n    if ($stype eq \"cdna\
\")\n      {\n	$cdna_seq=$seq;\n	$clean_cdna_seq=&\
vtmpnam();\n	$seq=&vtmpnam();\n	`t_coffee -other_p\
g seq_reformat -in $cdna_seq -action +clean_cdna >\
$clean_cdna_seq`;\n	`t_coffee -other_pg seq_reform\
at -in $clean_cdna_seq -action +translate >$seq`;\\
n	\n      }\n\n    if (!-e $msa || $recompute)\n  \
    {\n	print \"\\n#####   Compute an MSA With $al\
ignpg\\n\";\n	\n	if ( $alignpg eq \"t_coffee\")\n	\
  {`$alignpg $seq -outfile=$msa >/dev/null 2>/dev/\
null`;}\n	elsif ( $alignpg eq \"muscle\")\n	  {\n	\
    `$alignpg -in $seq > $msa 2>/dev/null`;\n	  }\\
n	elsif ( $alignpg eq \"clustalw\")\n	  {\n	    `$\
alignpg -infile=$seq -outfile=$msa -quicktree >/de\
v/null 2>/dev/null`;\n	  }\n	elsif ( $align eq \"m\
afft\")\n	  {\n	    `$alignpg $seq > $msa >/dev/nu\
ll 2>/dev/null`;\n	  }\n	else\n	  {\n	    `$alignp\
g -in=$seq -outfile=$msa`;\n	  }\n      }\n    if \
(!-e $msa)\n      {\n	print \"\\nError: $alignpg C\
ould Not produce the MSA $msa [FATAL]\\n\";\n     \
 }\n\n    if ($stype eq \"cdna\")\n      {\n	$msa2\
=\"$suffix.cdna_msa\";\n	`t_coffee -other_pg seq_r\
eformat -in $clean_cdna_seq -in2 $msa -action +thr\
ead_dna_on_prot_aln -output fasta_aln  >$msa2`;\n	\
$msa=$msa2;\n      }\n    \n    $input=\"msa\";\n \
 }\n\n\n\n$seqboot_o=&vtmpnam();\n$seqboot_c=&vtmp\
nam();\n\n$protdist_o=&vtmpnam();\n$protdist_c=&vt\
mpnam();\nif ( $input eq \"msa\")\n  {\n    if ($t\
mode eq \"nj\" || $tmode eq \"upgma\"){$input=\"ma\
trix\";}\n    \n    $lmsa= &vtmpnam ();\n    `t_co\
ffee -other_pg seq_reformat -in $msa -output phyli\
p_aln > $lmsa`;\n    \n    if ( -e \"outfile\"){un\
link (\"outfile\");}\n    # run seqboot\n  \n    i\
f ( $n>1)\n      {\n	print \"Run SeqBoot .....\";\\
n	open (F, \">$seqboot_c\");\n	print F \"$lmsa\\nR\
\\n$n\\nY\\n$seed\\n\";\n	close (F);\n	`seqboot$ex\
ec_extension  < $seqboot_c`;\n	if ( -e \"outfile\"\
){ print \"[OK]\\n\";}\n	else { print \"[FAILED]\\\
n\";&my_exit (EXIT_FAILURE);}\n	`mv outfile $seqbo\
ot_o`;\n      }\n    else\n      {\n	`cp $lmsa $se\
qboot_o`;\n      }\n\n    if ($rmsa){`cp $seqboot_\
o $rmsa`;}\n    \n    if ($tmode eq \"nj\" || $tmo\
de eq \"upgma\")\n      {\n	if ( $stype eq \"prot\\
")\n	  {\n	    # run protdist\n	    print \"Run Pr\
otdist [dmode=$dmode]\";\n	    if ($dmode eq \"kim\
ura\")\n	      {\n		$dmode=\"P\\nP\\nP\";\n	      \
}\n	    else\n	      {\n		print \"\\n$dmode is an \
unknown mode for Protdist [FATAL:msa2bootstrap.pl]\
\\n\";\n		&my_exit (EXIT_FAILURE);\n	      }\n	   \
 open (F, \">$protdist_c\");\n	    if ($n>1){print\
 F \"$seqboot_o\\n$dmode\\nM\\nD\\n$n\\nY\\n\";}\n\
	    else {printf F \"$seqboot_o\\n$dmode\\nY\\n\"\
;}\n	    close (F);\n	    `protdist$exec_extension\
  < $protdist_c`;\n	    if ( -e \"outfile\"){ prin\
t \"[OK]\\n\";}\n	    else { print \"[FAILED]\\n\"\
;&my_exit (EXIT_FAILURE);}\n	    `mv outfile $prot\
dist_o`;\n	 \n	  }\n	elsif ( $stype eq \"cdna\" ||\
 $stype eq \"dna\")\n	  {\n	    print \"Run dnadis\
t [dmode=default\";\n	    open (F, \">$protdist_c\\
");\n	    if ($n>1){print F \"$seqboot_o\\nM\\nD\\\
n$n\\nY\\n\";}\n	    else {printf F \"$seqboot_o\\\
nY\\n\";}\n	    close (F);\n	    `protdist$exec_ex\
tension  < $protdist_c`;\n	    if ( -e \"outfile\"\
){ print \"[OK]\\n\";}\n	    else { print \"[FAILE\
D]\\n\";&my_exit (EXIT_FAILURE);}\n	    `mv outfil\
e $protdist_o`;\n	  }\n      }\n  }\nelsif ( $inpu\
t eq \"matrix\")\n  {\n    $protdist_o=&vtmpnam();\
\n    print \"MSA: $msa\\n\";\n    `cp $msa $protd\
ist_o`;\n    $n=1;\n  }\n\n\n\n\n\n$nb_o=&vtmpnam(\
);\n$nb_c=&vtmpnam();\nif ($input eq \"matrix\" &&\
 $tmode ne \"parsimony\" && $tmode ne \"ml\")\n  {\
\n    print \"Run neighbor [tmode=$tmode]\";\n\n  \
  if ($tmode eq \"nj\")\n      {\n	$tmode=\"\\nN\\\
nN\";\n      }\n    elsif ( $tmode eq \"upgma\")\n\
      {\n	$tmode = \"\\nN\";\n      }\n    else\n \
     {\n	print \"\\n ERROR: $tmode is an unknown t\
ree computation mode\\n\";\n	&my_exit (EXIT_FAILUR\
E);\n      }\n\n    open (F, \">$nb_c\");\n    if \
($n>1){print F \"$protdist_o$tmode\\nM\\n$n\\n$see\
d\\nY\\n\";}\n    else {print F \"$protdist_o$tmod\
e\\nY\\n\";}\n    close (F);\n\n    `neighbor$exec\
_extension  < $nb_c`;\n    if ( -e \"outtree\"){ p\
rint \"[Neighbor OK]\\n\";}\n    else { print \"[F\
AILED]\\n\";&my_exit (EXIT_FAILURE);}\n    `mv out\
tree $nb_o`;\n    unlink (\"outfile\");\n  }\nelsi\
f ($input eq \"msa\" && $tmode eq \"parsimony\")\n\
  {\n    if ( -e \"outfile\"){unlink (\"outfile\")\
;}\n    if ( -e \"outtree\"){unlink (\"outtree\");\
}\n    \n    if ($stype eq \"prot\")\n      {\n	pr\
int \"Run protpars [tmode=$tmode]\";\n	open (F, \"\
>$nb_c\");\n	if ($n>1){print F \"$seqboot_o\\nM\\n\
D\\n$n\\n$seed\\n10\\nY\\n\";}\n	else {print F \"$\
seqboot_o\\nY\\n\";}\n	close (F);\n	`protpars$exec\
_extension  < $nb_c`;\n      }\n    elsif ( $stype\
 eq \"dna\" || $stype eq \"cdna\")\n      {\n	prin\
t \"Run dnapars [tmode=$tmode]\";\n	open (F, \">$n\
b_c\");\n	if ($n>1){print F \"$seqboot_o\\nM\\nD\\\
n$n\\n$seed\\n10\\nY\\n\";}\n	else {print F \"$seq\
boot_o\\nY\\n\";}\n	close (F);\n	`dnapars$exec_ext\
ension  < $nb_c`;\n      }\n    if ( -e \"outtree\\
"){ print \"[OK]\\n\";}\n    else { print \"[FAILE\
D]\\n\";&my_exit (EXIT_FAILURE);}\n    `mv outtree\
 $nb_o`;\n   unlink (\"outfile\");\n  }\nelsif ($i\
nput eq \"msa\" && $tmode eq \"ml\")\n  {\n    if \
( -e \"outfile\"){unlink (\"outfile\");}\n    if (\
 -e \"outtree\"){unlink (\"outtree\");}\n    \n   \
 if ($stype eq \"prot\")\n      {\n	print \"Error:\
 ML impossible with Protein Sequences [ERROR]\";\n\
	&my_exit (EXIT_FAILURE);\n      }\n    elsif ( $s\
type eq \"dna\" || $stype eq \"cdna\")\n      {\n	\
print \"Run dnaml [tmode=$tmode]\";\n	open (F, \">\
$nb_c\");\n	if ($n>1){print F \"$seqboot_o\\nM\\nD\
\\n$n\\n$seed\\n10\\nY\\n\";}\n	else {print F \"$s\
eqboot_o\\nY\\n\";}\n	close (F);\n	`dnaml$exec_ext\
ension  < $nb_c`;\n      }\n    if ( -e \"outtree\\
"){ print \"[OK]\\n\";}\n    else { print \"[FAILE\
D]\\n\";&my_exit (EXIT_FAILURE);}\n    `mv outtree\
 $nb_o`;\n   unlink (\"outfile\");\n  }\n\n\nelse\\
n  {\n    `cp $msa $nb_o`;\n    $n=2;\n  }\n\nif (\
$rmsa && -e $seqboot_o){print \"\\nOutput List of \
$n Replicate MSA: $rmsa\\n\";`cp $seqboot_o $rmsa`\
;}\nif ($rmat && -e $protdist_o){print \"\\nOutput\
 List of $n Replicate MATRICES: $rmat\\n\";`cp $pr\
otdist_o $rmat`;}\nif ($rtree && -e $nb_o){print \\
"\\nOutput List of $n Replicate TREES: $rtree\\n\"\
;`cp $nb_o $rtree`;}\n\n\n\n$con_o=&vtmpnam();\n$c\
on_c=&vtmpnam();\nif ($n >1)\n  {\n    print \"Run\
 Consense.....\";\n    open (F, \">$con_c\");\n   \
 print F \"$nb_o\\nY\\n\";\n    close (F);\n    `c\
onsense$exec_extension  < $con_c`;\n    if ( -s \"\
outtree\"  > 0) { print \"[OK]\\n\";}\n    else { \
print \"[FAILED]\\n\";&my_exit (EXIT_FAILURE);}\n \
   `mv outtree $con_o`;\n    unlink (\"outfile\");\
\n  }\nelse\n  {\n    `cp $nb_o $con_o`;\n  }\n\n\\
n`cp $con_o $out`;\nif ( !-e $out)\n  {\n    print\
 \"Tree Computation failed [FAILED]\\n\";\n    &my\
_exit (EXIT_FAILURE);\n  }\nelsif ($n>1)\n  {\n   \
 print \"\\nOutput Bootstrapped Tree: $out\\n\";\n\
    $avg=`t_coffee -other_pg seq_reformat -in $out\
 -action +avg_bootstrap`;\n    $avg=~s/\\n//g;\n  \
  print \"$avg\\n\";\n  }\nelse\n  {\n    print \"\
\\nOutput Tree: $out\\n\";\n  }\n\nopen (F, \"$out\
\");\nwhile (<F>)\n  {\n    \n    $tree.=$_;\n  }\\
nclose (F);\n$tree=~s/\\n//g;\nprint \"BPH: $tree\\
\n\";\n\n\n&my_exit (EXIT_SUCCESS);\n\nsub my_exit\
 \n  {\n    my $m=@_[0];\n    &clean_vtmpnam();\n \
   exit ($m);\n  }\nsub vtmpnam \n  {\n    my $fil\
e;\n\n\n    $ntmp++;\n    $file=\"tmp4msa2bootstra\
p.$rseed.$$.$ntmp\";\n    \n    push (@tmpfile, $f\
ile);\n    return $file;\n  }\nsub clean_vtmpnam \\
n  {\n    my $t;\n    foreach $t (@tmpfile)\n     \
 {\n	if ( -e $t){unlink ($t)};\n      }\n  }\n","u\
se Env;\n$seq_reformat=\"t_coffee -other_pg seq_re\
format \";\n$VersionTag=\"1.00\";\n$step=1;\n$unse\
t=\"\";\n$scoreT1=$scoreT2=$nseqT=$dp_limit=$unset\
;\n@tl=();\nchomp($tc_version=`t_coffee -version`)\
;$tc_version=~s/PROGRAM: //;\n\n\nprint STDERR \"\\
\n************************************************\
*****************\";\nprint STDERR \"\\n*         \
  HIGH LEVEL PROGRAM: T-COFFEE_DPA Version $Versio\
nTag\";\nprint STDERR \"\\n*           LOW  LEVEL \
PROGRAM: $tc_version \";\nprint STDERR \"\\n******\
**************************************************\
*********\";\n\nif (!@ARGV)\n  {\n    print \"t_co\
ffee_dpa accepts every t_coffee_flag.\\nType t_cof\
fee to obtain a list\\n\";\n    print \"Requires $\
TC_VERSION\\n\";\n    print \"Requires \";\n    pr\
int \"t_coffee_dpa specific flags:\\n\";\n    prin\
t \"\\t-dpa_master_aln....................Master a\
lignment: provided OR computed\\n\";\n    print \"\
\\t-dpa_master_aln....................By default, \
Computed with t_coffee -very_fast\\n\";\n    print\
 \"\\t-dpa_master_aln=<file>.............Use file,\
 (must be an aln in Fasta or ClustalW\\n\";\n    p\
rint \"\\t-dpa_master_aln=<program>..........Compu\
te aln with pg -in seq -out aln`\\n\";\n    print \
\"\\t-dpa_maxnseq.......................Maximum nu\
mber of sequences in subgroups\\n\";\n    print \"\
\\t-dpa_min_score1....................Minimum Id f\
or two sequences to be grouped in ref_aln\\n\";\n \
   print \"\\t-dpa_min_score2....................M\
inimum Id within a subgroup\\n\";\n    print \"\\t\
-dpa_debug.........................Keep Tmp File (\
for debug purpose)\\n\\n\";\n    \n    exit (0);\n\
  }\nforeach $arg (@ARGV)\n  {\n    $arg_list.=\" \
$arg\";\n  }\n$arg_list=~s/[=,;]/ /g;\n\n\n($seq0,\
 $arg_list)=&extract_val_from_arg_list(\"^\",$arg_\
list, \"SPLICE\",\"unset\");\n($seq1, $arg_list)=&\
extract_val_from_arg_list(\"-seq\",$arg_list, \"SP\
LICE\",\"unset\");\n($seq2, $arg_list)=&extract_va\
l_from_arg_list(\"-in\",$arg_list, \"KEEP\",\"unse\
t\");\n($seq3, $arg_list)=&extract_val_from_arg_li\
st(\"-infile\",$arg_list, \"SPLICE\",\"unset\");\n\
($prf,  $arg_list)=&extract_val_from_arg_list(\"-p\
rofile\",$arg_list, \"SPLICE\",\"unset\");\n\n$gl{\
'Seq'}=$seq=&vtmpnam();#file containing all the se\
quences\n\n   #1-remove sequences from -in\nif ( $\
arg_list =~/\\-in\\b/)\n  {\n    my $save, $name;\\
n    while($arg_list=~/\\-in\\b[^-]+(\\bS[\\w.]+)/\
)\n      {\n	$name=$1;$name=~s/^.//;\n	if ( !-e $n\
ame){$save.=\" S$name \";}\n\n	$arg_list=~s/S$name\
/ /;\n      }\n    $arg_list=~s/\\-in\\b/\\-in $sa\
ve /;\n  }\n   #2-prepare \n\nif (!($arg_list=~/\\\
-outorder/))\n  {\n    \n    $output_cl .=\" -outo\
rder=$seq\";\n  }\n@output_flag=(\"-output\",\"-ou\
tfile\", \"-run_name\", \"-outorder\"); \nforeach \
$v1 (@output_flag)\n  {\n    ($v2, $arg_list)=&ext\
ract_val_from_arg_list($v1,$arg_list, \"SPLICE\",\\
"unset\");\n    if ($v2 ne \"\")\n      {\n\n	if (\
$v1 eq \"-run_name\"){$run_name=$v2;$output_cl .=\\
" $v1 $v2 \";}\n	elsif ( $v1 eq \"-outorder\")\n	 \
 {\n	    if ( $v2 eq \"input\"){$v2=$seq;}\n	    $\
outorder=$v2;$output_cl .=\" $v1 $v2 \";\n	  }\n	e\
lse\n	  {\n	    $output_cl .=\" $v1 $v2 \";\n	  }\\
n      }\n }\n\n\n($dpa_master_aln, $arg_list)  =&\
extract_val_from_arg_list(\"-dpa_master_aln\",$arg\
_list, \"SPLICE\", \"t_coffee\");\n$dpa_master_aln\
=~s/\\s//g;\n($nseqT, $arg_list)           =&extra\
ct_val_from_arg_list(\"-dpa_maxnseq\",$arg_list, \\
"SPLICE\", 30);\n($scoreT1, $arg_list)         =&e\
xtract_val_from_arg_list(\"-dpa_min_score1\",$arg_\
list, \"SPLICE\", 80);\n($scoreT2, $arg_list)     \
    =&extract_val_from_arg_list(\"-dpa_min_score2\\
"    ,$arg_list, \"SPLICE\", 30);\n($dpa_limit, $a\
rg_list)       =&extract_val_from_arg_list(\"-dpa_\
limit\"        ,$arg_list, \"SPLICE\", 0);\n($dpa_\
delta_id, $arg_list)    =&extract_val_from_arg_lis\
t(\"-dpa_delta_id\"        ,$arg_list, \"SPLICE\",\
 1);\n($dpa_debug, $arg_list)       =&extract_val_\
from_arg_list(\"-dpa_debug\"           ,$arg_list,\
 \"SPLICE\", 0);\n\n\n$in_seq=$seq0.\" \".$seq1.\"\
 \".$seq2.\" \".$seq3;\n$in_prf=(($prf ne $unset)?\
\"$prf \":\"\");\n&exit_dpa (($in_seq eq \"\" && $\
in_prf eq \"\")?1:0, \"ERROR: You did not Provide \
any sequences. Use the -seq flag [FATAL: t_coffee_\
dpa]\\n\", EXIT_FAILURE);\n\n\nprint STDERR \"\\nS\
TART DPA COMPUTATION\";\n\n\n\nif ($in_seq=~/\\S+/\
)\n  {\n    \n    print STDERR \"\\n Step $step: G\
ather all the sequences into the tmp file: [$seq]\\
";$step++;	\n    &my_system (\"t_coffee $in_seq -c\
onvert -quiet -output fasta_seq -outfile=$seq -max\
nseq 0\");\n  }\n\nif ( !-e $seq){$seq=\"\";}\n\ni\
f ($in_prf=~/\\S+/)\n  {\n    $seq_in_type=\"profi\
le\"; \n    $seq.= $in_prf; \n  }\nif ($seq eq \"\\
"){ &exit_dpa (1, \"\\nERROR: No Sequence FOund. P\
rovide Sequences with the -seq flag [FATAL: t_coff\
ee_dpa]\", EXIT_FAILURE);}\n\n \n\nif ( $run_name)\
\n  {\n    $suffix=$run_name;\n  }\nelsif ($in_seq\
=~/\\b(S[\\w.]+\\b)/)\n  {\n    my $suffix1, $suff\
fix2;\n    $suffix1=$suffix2=$1;\n    $suffix2=~s/\
^S//;\n    if ( -e $suffix1){$suffix=$suffix1;}\n \
   elsif ( -e $suffix2){$suffix=$suffix2;}\n    el\
se\n      {\n	$suffix=&vtmpnam();	\n      }\n    $\
suffix=~s/\\.\\w+//;\n  }\n\nelse\n  {\n    $suffi\
x=&vtmpnam();\n  }\n\n\nif (!$run_name){$output_cl\
.=\" -run_name $suffix \";}\n\n\n$gl{'Tree'}=&seq2\
dpa_tree ($seq, \"$suffix.dpadnd\");\n\nprint STDE\
RR \"\\n Step $step: Prepare guide tree: $gl{'Tree\
'}\";$step++;\n\nprint STDERR \"\\n Step $step: Id\
entify and Align Closely Related Groups\";$step++;\
\n%gl=&make_one_pass (0, $scoreT1,\"Align\",%gl);\\
n\nprint STDERR \"\\n Step $step: Make Multiple Gr\
oup Alignment\";$step++;\nwhile (!%gl ||$gl{'Ng'}>\
$nseqT)\n  {\n    %gl=&make_one_pass ($nseqT, $sco\
reT2,\"t_coffee\",%gl);\n    if ( $gl{'Newgroups'}\
==0){$scoreT2--;}    \n  }\nprint STDERR \"\\n Ste\
p $step: Make The Final Alignment\";$step++;\n\n\n\
$arg_list .=$output_cl;\n\n\n%gl=&tree2group (0,0,\
 %gl);\n$gl{$gl{'0'}{'File'}}{'Output'}=\"\";\n$a=\
0;\n&align_groups (\"t_coffee\",'0', $arg_list, \"\
 \", %gl);\n\n\n\nif ( !$dpa_keep_tmpfile){&clean_\
tmp_file (@tl);}\n\n\n\nsub seq2dpa_tree \n  {\n  \
  my $seq=@_[0];\n    my $newtree=@_[1];\n    my $\
aln=&vtmpnam ();\n\n    &my_system (\"t_coffee -sp\
ecial_mode quickaln -in $seq -outfile $aln -quiet\\
");\n    &my_system (\"$seq_reformat -in $aln -act\
ion +aln2tree +tree2dpatree -output newick >$newtr\
ee\");\n    return $newtree;\n  }	\nsub seq2dpa_tr\
ee_old \n  {\n    my $aln=@_[0];\n    my $newtree=\
@_[1];\n    \n    \n    &my_system(\"$seq_reformat\
 -in $aln -action +seq2dpatree -output newick > $n\
ewtree\");\n    return $newtree;\n  }\nsub aln2dpa\
_tree \n  {\n    my $aln=@_[0];\n    my $newtree=&\
vtmpnam();\n    \n    &my_system(\"$seq_reformat -\
in $aln -action +aln2tree +tree2dpatree -output ne\
wick > $newtree\");\n    return $newtree;\n  }\nsu\
b group_file2ngroups\n  {\n    my $file=@_[0];\n  \
  my $n;\n    \n    open ( F, $file);\n    while (\
<F>)\n      {\n	$n+=/\\>/;\n      }\n    close (F)\
;\n    return $n;\n  }\n\nsub make_one_pass\n  {\n\
    my ($N, $ID,$pg, %gl)=@_;\n    my $a;\n\n    %\
gl=&tree2group ($N,$ID,%gl);\n    if (!$gl{'Newgro\
ups'}){return %gl;}\n    else\n      {\n	for ( $a=\
0; $a< $ng; $a++)\n	  {\n	    if ($gl{$gl{$a}{'Fil\
e'}}{'Ng'}>1){&display_group($a, %gl);}\n	    &ali\
gn_groups ($pg, $a, $arg_list, \" -quiet=quiet \",\
 %gl);\n	  }\n	return %gl;\n      }\n  }\n\nsub tr\
ee2group \n  {\n    my ($N, $ID, %gl)=@_;\n    my \
$prefix=&vtmpnam();\n    my $group_file=&vtmpnam()\
;\n    my $file;\n    my $oldtree=&vtmpnam();\n   \
 my $n;\n    my $tree;\n\n\n    if ( $gl{'Ng'}==1)\
{return %gl;}\n    $tree=$gl{'Tree'}; \n    \n    \
#1 extract the groups\n    &my_system (\"$seq_refo\
rmat -in $tree -action +tree2group $N $ID $prefix \
> $group_file\");\n    $n=group_file2ngroups($grou\
p_file);\n    \n    \n    $gl{'Newgroups'}=1;\n   \
 if ( $n==$gl{'Ng'})\n      {\n	$gl{'Newgroups'}=0\
;\n	return %gl;\n      }\n    $gl{'Iteration'}++;\\
n    $gl{'MaxNseq'}=$N;$gl{'MinID'}=$ID;\n    $gl{\
'GroupFile'}=$group_file;$gl{'Ng'}=$ng=0;\n    #2 \
Process the group list into the hash\n    open (F,\
 $group_file);\n    while (<F>)\n      {\n	$gl{'Fi\
le'}.=$_;\n	if (/\\>/)\n	  {\n	    $line=$_;\n	   \
 $line=~s/\\>//;\n	    @list=($line=~/(\\S+)/g);\n\
	    $file=$gl{$ng}{'File'}=shift @list;\n	    $gl\
{$file}{'Output'}=$file;\n	    \n	    $gl{$file}{'\
Ng'}=$#list+1;\n	    if ($gl{$file}{'Ng'}>1){ $gl{\
$file}{'Tlist'}=$gl{$file}{'Alist'}=\"(\";}\n	    \
foreach $l (@list)\n	      {\n	\n		$gl{$file}{'Lis\
t'}.=\" $l \";\n		\n		if (!$gl{$l}{'Tlist'})\n		  \
{\n		    $gl{$l}{'Tlist'}=\"$l\";\n		    $gl{$l}{'\
Alist'}=\"$l\";\n		    $gl{$l}{'Nseq'}=1;\n		    $\
gl{$l}{'Ng'}=1;\n		  }\n		$gl{$file}{'Tlist'}.=\"$\
gl{$l}{'Tlist'},\";\n		$gl{$file}{'Alist'}.=\"$gl{\
$l}{'Tlist'}|\";\n		$gl{$file}{'Nseq'}+=$gl{$l}{'N\
seq'};\n	      }\n	    \n\n	    chop($gl{$file}{'T\
list'});chop($gl{$file}{'Alist'});\n	    if ($gl{$\
file}{'Ng'}>1){$gl{$file}{'Tlist'}.=\")\"; $gl{$fi\
le}{'Alist'}.=\");\";}\n	    $ng++;\n	  }	\n      \
}\n    $gl{'Ng'}=$ng;\n    close (F);\n    \n    #\
3 Update the old tree with the new groups\n    $gl\
{'Tree'}=&vtmpnam();\n    &my_system (\"$seq_refor\
mat -in $tree -action +collapse_tree $group_file -\
output newick > $gl{'Tree'}\");\n    \n    return \
%gl;\n  }\n\nsub display_group \n  {\n    my ($g,%\
gl)=@_;\n    my $f;\n    \n    if ( $g==-1)\n     \
 {\n	print STDERR \"\\nIteration $gl{'Iteration'} \
[MaxN=$gl{'MaxNseq'}][MinID=$gl{'MinID'}]\";\n    \
  }\n    else\n      {\n\n	$f=$gl{$g}{'File'};\n	$\
action=($gl{$f}{'Ng'}==1 || $gl{'Iteration'}==1)?\\
"KEEP  \":\"ALIGN \";\n        print STDERR \"\\n\\
\t[$action][MaxN=$gl{'MaxNseq'}][MinID=$gl{'MinID'\
}][File $f][Nseq=$gl{$f}{'Nseq'}][Ngroups=$gl{$f}{\
'Ng'}][$gl{$f}{'Alist'}]\";\n      }\n  }\n      \\
n\n\nsub align_groups\n  {\n    my ($pg, $g, $arg,\
 $extra_arg,%gl)=@_;\n    my $f;\n    my $Output,$\
Outflag;\n    \n    \n    $f=$gl{$g}{'File'};\n   \
 $Output=($gl{$f}{'Output'});\n    \n    if ( $pg \
eq \"Align\")\n      {\n	if ( !-e $f)\n	  {\n	    \
$command=\"$seq_reformat -in $gl{'Seq'}  -action +\
extract_aln $gl{'GroupFile'}\";\n	    if ($gl{$f}{\
'Ng'}>1)\n	      {\n		&my_system ($command);\n		$c\
ommand=\"t_coffee -special_mode quick_aln  S$f -ou\
tfile=$Output -quiet\";\n	      }\n	  }\n	else \n	\
  {$command=\"\";}\n      }\n    elsif ( -e $f)\n \
     {	\n	$Outflag=($Output)?\"-outfile=$Output\":\
\"\";\n	$command=\"$pg -infile $f $Outflag -quiet \
stdout $arg $extra_arg -maxnseq 0 -convert -quiet \
stdout\";\n      }\n    elsif ( $gl{$f}{'Ng'}==1)\\
n      {\n	$action=($dpa_debug)?\"cp\":\"mv\";\n	$\
command=\"$action $gl{$f}{'List'} $Output\";\n    \
  }\n    else\n      {\n	$Outflag=($Output)?\"-out\
file=$Output\":\"\";\n	$command=\"$pg -profile $gl\
{$f}{'List'} $Outflag $arg $extra_arg -maxnseq 0\"\
;\n      }\n    \n    &my_system ($command);\n    \
return $outfile;\n  }\n    \nsub my_system \n  {\n\
    my $command=@_[0];\n    my $force=@_[1];\n    \
my $status;\n\n    if ( $dpa_debug) {print STDERR \
\"\\nCOMMAND: $command\";}\n    $status=system ($c\
ommand);\n\n    if (!$force)\n       {\n	 &exit_dp\
a (($status==1), \"Failed in Command:\\n$command\\\
n[FATAL: t_coffee_dpa]\\n\", EXIT_FAILURE);\n     \
  }\n    \n    return $status;\n  }\n\nsub vtmpnam\
\n  {\n    my $prefix=@_[0];\n    my $tmp_file_nam\
e;\n\n    $tmp_prefix=($prefix)?$prefix:\"dpa_tmp_\
file_$$\";\n   \n    $tmp_count++;\n    $tmp_file_\
name=\"$tmp_prefix\".\"$tmp_count\";\n    $tl[$#tl\
+1]=$tmp_file_name;\n    return $tmp_file_name;\n \
 }\n\nsub clean_tmp_file\n  {\n\n    my $list;\n  \
  my $file;\n    \n    if ($dpa_debug){return;}\n \
   $list=vtmpnam();\n    `ls -1 | grep $tmp_prefix\
>$list`;\n    \n    open (F,$list);\n    while ( <\
F>)\n      {\n	$file=$_;\n	chop $file;\n	if ( -e $\
file){unlink $file;}\n      }\n    close (F);\n   \
 unlink $list;\n  }\n\n\nsub exit_dpa\n  {\n  my $\
condition=@_[0];\n  my $error_msg=@_[1];\n  my $ex\
it_value=@_[2];\n  if ( $condition)\n    {\n      \
print \"$error_msg\\n\";\n      exit ($exit_value)\
;\n    }\n  else\n    {\n      return;\n    }\n  \\
n}\nsub extract_val_from_arg_list\n  {\n    my $ar\
g=@_[0];\n    my $arg_list=@_[1];\n    my $keep_fl\
ag=@_[2];\n    my $default_value=@_[3];\n    my $v\
al=\"\";\n    \n    #protect\n    $arg_list=~s/\\s\
-/ \\@/g;\n    $arg=~s/-/\\@/g;\n    \n    #search\
\n    if ($arg eq \"^\")\n      {\n	$arg_list=~/^(\
[^@]*)/;\n	$val=$1;\n      }\n    else\n      {$ar\
g_list=~/$arg ([^@]*)/;$val=$1;}\n    \n    #remov\
e trailing spaces\n    $val=~s/\\s*$//;\n    \n   \
 #remove the parsed sequence if needed\n    if (($\
val ne \"\") && $keep_flag ne \"KEEP\")\n      {\n\
	if ( $arg eq \"^\"){$arg_list=~s/$val/ /;}\n	else\
 {$arg_list=~s/($arg [^@]*)/ /;}\n      }\n	\n    \
#unprotect\n    $arg_list=~s/\\@/-/g;\n    $arg=~s\
/\\@/-/g;\n    \n    if (($val eq \"\") && $defaul\
t_value ne \"unset\"){$val=$default_value;}\n    \\
n    return $val, $arg_list;\n  }\n$program=\"T-CO\
FFEE (dev_brew@20170304_17:15)\";\n\n","\n$DEBUG=1\
;\n$dpa_nseq=10;\n$dpa_sim=0;\nif (!@ARGV)\n  {\n \
   `t_coffee`;\n    exit (0);\n  }\nforeach $arg (\
@ARGV)\n  {\n    $arg_list.=\" $arg\";\n  }\n$max_\
nseq=10;\n($seq0, $arg_list)=&extract_val_from_arg\
_list(\"^\",$arg_list);\n($seq1, $arg_list)=&extra\
ct_val_from_arg_list(\"-seq\",$arg_list);\n($seq2,\
 $arg_list)=&extract_val_from_arg_list(\"-in\",$ar\
g_list, \"KEEP\");\n($seq3, $arg_list)=&extract_va\
l_from_arg_list(\"-infile\",$arg_list);\n$in_seq=$\
seq0.\" \".$seq1.\" \".$seq2.\" \".$seq3;\n\n$seq=\
vtmpnam();\n`t_coffee $in_seq -convert -output fas\
ta_seq -outfile=$seq`;\n\n\n($dpa_nseq, $arg_list)\
=&extract_val_from_arg_list(\"-dpa_nseq\",$arg_lis\
t);\n($master_aln, $arg_list)=&extract_val_from_ar\
g_list(\"-master_aln\",$arg_list);\n($sim_matrix, \
$arg_list)=&extract_val_from_arg_list(\"-sim_matri\
x\",$arg_list);\n($core_seq, $arg_list)=&extract_v\
al_from_arg_list(\"-core_seq\",$arg_list);\n($dpa_\
sim, $arg_list)=&extract_val_from_arg_list(\"-dpa_\
sim\",$arg_list);\n($run_name, $arg_list)=&extract\
_val_from_arg_list(\"-run_name\",$arg_list);\n($ou\
tput, $arg_list)=&extract_val_from_arg_list(\"-out\
put\",$arg_list);\n\n\n\nif (!$sim_mat && !$master\
_aln)#Compute the fast alignment\n  {\n    $ref_al\
n=vtmpnam();\n    `t_coffee -seq=$seq -very_fast -\
outfile=$ref_aln -quiet`;\n    \n  }\n\nif (!$sim_\
mat)\n  {\n    $sim_mat=vtmpnam();\n    `seq_refor\
mat -in $ref_aln -output sim > $sim_mat`;\n  }\n\n\
if ( !$core_seq)\n  {\n    $core_seq=vtmpnam();\n \
   `seq_reformat -in $ref_aln -action +trimTC N$ma\
x_nseq -output fasta_seq > $core_seq`;\n  }\n@core\
_name=`seq_reformat -in $core_seq -output name `; \
\n\n@tot_name=`seq_reformat -in $seq -output name \
`;\n\nforeach $s (@core_name){$s=~s/\\s//g;$hcore{\
$s}=1;}\nforeach $s (@tot_name){$s=~s/\\s//g;}\npr\
int STDERR \"T-Coffee_dpa:\\n\";\nprint STDERR \"\\
\tTOTAL  SEQ: @tot_name\\n\";\nprint STDERR \"\\tC\
HOSEN SEQ: @core_name\\n\";\n\n\n\nopen (F, $sim_m\
at);\nwhile ( <F>)\n  {\n    @l=($_=~/(\\b[\\S]+\\\
b)/g);\n    if (($l[0] eq \"TOP\" || $l[0] eq \"BO\
T\"))\n      {\n	$s1=$l[1];$s2=$l[2];$v=$l[3];\n	i\
f ($hcore{$s1} && !$hcore{$s2})\n	  {\n	    if (!$\
hseq{$s2}{\"sim\"} || $v>$hseq{$s2}{\"sim\"})\n	  \
    {\n		$hseq{$s2}{\"sim\"}=$v;$hseq{$s2}{\"seq\"\
}=$s1;\n	      }\n	  }\n      }\n  }\nclose (F);\n\
foreach $s (@tot_name)\n  {\n\n    if ( !$hseq{$s}\
{\"seq\"}){;}\n    else\n      {\n	$s2=$hseq{$s}{\\
"seq\"};\n	$v=$hseq{$s}{\"sim\"};\n		\n	if ($v>$dp\
a_sim)\n	  {\n	    $hseq{$s}{'used'}=1;\n	    $seq\
_list{$s2}{$seq_list{$s2}{'nseq'}++}=$s;\n	  }\n  \
    }\n  }\nforeach $s (@core_name){$seq_list{$s}{\
$seq_list{$s}{'nseq'}++}=$s;$hseq{$s}{'used'}=1;}\\
nforeach $s (@tot_name){if (!$hseq{$s}{'used'}){$s\
eq_list{'unused'}{$seq_list{'unused'}{'nseq'}++}=$\
s;}}\n\n\n$n=0;\nforeach $s (@core_name)\n  {\n   \
 $ng++;\n    $n=$seq_list{$s}{'nseq'};\n    for (@\
g_list=(), $a=0; $a<$n; $a++){@g_list=(@g_list,$se\
q_list{$s}{$a});}\n\n    $g_seq=vtmpnam();\n    $g\
_aln=vtmpnam();\n    \n    print STDERR \"Group $n\
g: $#g_list Seq: @g_list: \";\n    \n    \n    `se\
q_reformat -in $seq -action +lower +keep_name +ext\
ract_seq  @g_list -output fasta_seq > $g_seq`;\n  \
  \n    \n    if ( $#g_list==0)\n      {\n	print S\
TDERR \"[No aln]\\n\";\n	$g_aln=$g_seq;\n      }\n\
    elsif ($#g_list<$max_nseq) \n      {\n	print S\
TDERR \"[t_coffee]\\n\";\n	`t_coffee $g_seq -outfi\
le=$g_aln -quiet $arg_list`;\n      }\n    else\n \
     {\n	print STDERR \"[t_coffee_dpa]\\n\";\n	`t_\
coffee_dpa2 $g_seq -outfile=$g_aln $arg_list -sim_\
matrix $sim_matrix -dpa_nseq $dpa_nseq`;\n      }\\
n    @profile_list=(@profile_list, $g_aln);\n  }\n\
\n\nprint \"UNUSED $seq_list{'unused'}{'nseq'}\";\\
n\nif ($seq_list{'unused'}{'nseq'})\n    {\n      \
$prf=vtmpnam();\n      \n      `t_coffee -profile \
@profile_list $arg_list -outfile=$prf -quiet`;\n  \
    $n=$seq_list{\"unused\"}{'nseq'};\n      $new_\
seq=vtmpnam();\n      $new_prf=vtmpnam();\n      f\
or ($a=0; $a<$n-1; $a++)\n	{\n	  $s=$seq_list{\"un\
used\"}{$a};\n	  print STDERR \"\\nADD Sequence $s\
\";\n	  \n	  `seq_reformat -in $seq -action +lower\
 +keep_name +extract_seq $s  -output fasta_seq > $\
new_seq`;\n	  `t_coffee -profile $prf $new_seq $ar\
g_list -outfile=$new_prf`;\n	  `cp $new_prf $prf`;\
\n	}\n      $s=$seq_list{\"unused\"}{$a};\n      `\
seq_reformat -in $seq -action +lower +keep_name +e\
xtract_seq $s  -output fasta_seq > $new_seq`;\n   \
   @profile_list=($prf, $new_seq);\n    }\n    \n \
     \nif ($run_name){$arg_list.=\" -run_name $run\
_name\";}\nelse \n  {\n    $in_seq=~/([\\w-]+)/;\n\
    $arg_list.=\" -run_name $1\";\n  }\nif ( $outp\
ut){$arg_list.=\" -output $output \";}\n\n`t_coffe\
e -profile @profile_list $arg_list`;\n\n\n&clean (\
@tmp_file_list);\n\n\nsub vtmpnam\n  {\n    my $tm\
p_file_name;\n    $tmp_name_counter++;\n    $tmp_f\
ile_name=\"tmp_file_$tmp_name_counter\\_Pid$$\";\n\
    $tmp_file_list[$ntmp_file++]=$tmp_file_name;\n\
    return $tmp_file_name;\n  }\nsub clean\n  {\n \
 my @fl=@_;\n  my $file;\n  return;\n\n  foreach $\
file ( @fl)\n    {\n      if ( -e $file){unlink($f\
ile);}\n    }\n}\nsub extract_val_from_arg_list\n \
 {\n    my $arg=@_[0];\n    my $arg_list=@_[1];\n \
   my $keep_flag=@_[2];\n    #protect\n    $arg_li\
st=~s/\\s-/ \\@/g;\n    $arg=~s/-/\\@/g;\n    \n  \
  #search\n    if ($arg eq \"^\")\n      {\n	$arg_\
list=~/^([^@]*)/;\n	$val=$1;\n      }\n    else\n \
     {$arg_list=~/$arg ([^@]*)/;$val=$1;}\n    \n \
   #remove the parsed sequence if needed\n    if (\
$val && $keep_flag ne \"KEEP\")\n      {\n	if ( $a\
rg eq \"^\"){$arg_list=~s/$val/ /;}\n	else {$arg_l\
ist=~s/($arg [^@]*)/ /;}\n      }\n	\n    #unprote\
ct\n    $arg_list=~s/\\@/-/g;\n    $arg=~s/\\@/-/g\
;\n    \n    return $val, $arg_list;\n  }\n\n","us\
e Env;\nuse FileHandle;\nuse Cwd;\nuse File::Path;\
\nuse Sys::Hostname;\n\nour $PIDCHILD;\nour $ERROR\
_DONE;\nour @TMPFILE_LIST;\nour $EXIT_FAILURE=1;\n\
our $EXIT_SUCCESS=0;\n\nour $REFDIR=getcwd;\nour $\
EXIT_SUCCESS=0;\nour $EXIT_FAILURE=1;\n\nour $PROG\
RAM=\"tc_generic_method.pl\";\nour $CL=$PROGRAM;\n\
\nour $CLEAN_EXIT_STARTED;\nour $debug_lock=$ENV{\\
"DEBUG_LOCK\"};\nour $debug_generic_method=$ENV{\"\
DEBUG_GENERIC_METHOD\"};\nour $LOCKDIR=$ENV{\"LOCK\
DIR_4_TCOFFEE\"};\nif (!$LOCKDIR){$LOCKDIR=getcwd(\
);}\nour $ERRORDIR=$ENV{\"ERRORDIR_4_TCOFFEE\"};\n\
our $ERRORFILE=$ENV{\"ERRORFILE_4_TCOFFEE\"};\n&se\
t_lock ($$);\nif (isshellpid(getppid())){lock4tc(g\
etppid(), \"LLOCK\", \"LSET\", \"$$\\n\");}\nour %\
RECODE;\nour $RECODE_N;\n\n\n\n\nour $BLAST_MAX_NR\
UNS=2;\nour $COMMAND;\nour $PIDCHILD;\n\n$REF_EMAI\
L=\"\";\n$tmp_dir=\"\";\n$init_dir=\"\";\n\n\n$tes\
t=0;\nif ($test==1)\n  {\n    $SERVER=\"NCBI\";\n \
   $query=$ARGV[0];\n    $hitf=$ARGV[1];\n    %s=r\
ead_fasta_seq($query);\n    @sl=keys(%s);\n    &bl\
ast_xml2profile (\"xx\", $s{$sl[0]}{seq},$maxid,$m\
inid,$mincov, $hitf);\n    myexit ($EXIT_FAILURE);\
\n  }\n\nforeach $v(@ARGV){$cl.=\"$v \";}\n$COMMAN\
D=$cl;\n($mode)=&my_get_opt ( $cl, \"-mode=\",1,0)\
;\n\n($A)=(&my_get_opt ( $cl, \"-name1=\",0,0));\n\
($B)=(&my_get_opt ( $cl, \"-name2=\",0,0));\n($TMP\
DIR)=(&my_get_opt ( $cl, \"-tmpdir=\",0,0));\n($CA\
CHE)=(&my_get_opt ( $cl, \"-cache=\",0,0));\n($SER\
VER)=((&my_get_opt ( $cl, \"-server=\",0,0)));\n($\
EMAIL)=((&my_get_opt ( $cl, \"-email=\",0,0)));\n\\
nif (!$A){$A=\"A\";}\nif (!$B){$B=\"B\";}\n\n\nif \
(!$TMPDIR)\n  {\n    $HOME=$ENV{HOME};\n    if ($E\
NV{TMP_4_TCOFFEE}){$TMPDIR=$ENV{TMP_4_TCOFFEE};}\n\
    else{$TMPDIR=\"$HOME/.t_coffee/tmp/\";}\n  }\n\
if ( ! -d $TMPDIR)\n  {\n    mkdir $TMPDIR;\n  }\n\
if ( ! -d $TMPDIR)\n  {\n    print \"ERROR: Could \
not create temporary dir: $TMPDIR\\n\";\n    myexi\
t ($EXIT_FAILURE);\n  }\n\n$EMAIL=~s/XEMAILX/\\@/g\
;\nif (!$EMAIL)\n  {\n    if ($ENV{EMAIL_4_TCOFFEE\
}){$EMAIL=$ENV{EMAIL_4_TCOFFEE};}\n    elsif ($ENV\
{EMAIL}){$EMAIL=$ENV{EMAIL};}\n    else {$EMAIL=$R\
EF_EMAIL;}\n  }\n\n($maxid,$minid,$mincov)=(&my_ge\
t_opt ( $cl, \"-maxid=\",0,0, \"-minid=\",0,0,\"-m\
incov=\",0,0));\nif (!$cl=~/\\-maxid\\=/){$maxid=9\
5;}\nif (!$cl=~/\\-minid\\=/){$minid=35;}\nif (!$c\
l=~/\\-mincov\\=/){$mincov=80;}\n\n\n\n\nif ($mode\
 eq \"seq_msa\")\n  {\n    &seq2msa($mode,&my_get_\
opt ( $cl, \"-infile=\",1,1, \"-method=\",1,2, \"-\
param=\",0,0,\"-outfile=\",1,0, \"-database=\",0,0\
));\n  }\nelsif ( $mode eq \"tblastx_msa\")\n  {\n\
    &seq2tblastx_lib ($mode,&my_get_opt ( $cl, \"-\
infile=\",1,1, \"-outfile=\",1,0));\n  }\nelsif ( \
$mode eq \"tblastpx_msa\")\n  {\n    &seq2tblastpx\
_lib ($mode,&my_get_opt ( $cl, \"-infile=\",1,1, \\
"-outfile=\",1,0));\n  }\nelsif ( $mode eq \"threa\
d_pair\")\n  {\n    &seq2thread_pair($mode,&my_get\
_opt ( $cl, \"-infile=\",1,1, \"-pdbfile1=\",1,1, \
\"-method=\",1,2,\"-param=\",0,0, \"-outfile=\",1,\
0, ));\n  }\nelsif ( $mode eq \"pdbid_pair\")\n  {\
\n    &seq2pdbid_pair($mode,&my_get_opt ( $cl, \"-\
pdbfile1=\",1,0, \"-pdbfile2=\",1,0, \"-method=\",\
1,2,\"-param=\",0,0, \"-outfile=\",1,0, ));\n  }\n\
elsif ( $mode eq \"pdb_pair\")\n  {\n    &seq2pdb_\
pair($mode,&my_get_opt ( $cl, \"-pdbfile1=\",1,1, \
\"-pdbfile2=\",1,1, \"-method=\",1,2,\"-param=\",0\
,0, \"-outfile=\",1,0, ));\n  }\nelsif ( $mode eq \
\"profile_pair\")\n  {\n     &seq2profile_pair($mo\
de,&my_get_opt ( $cl, \"-profile1=\",1,1, \"-profi\
le2=\",1,1, \"-method=\",1,2,\"-param=\",0,0, \"-o\
utfile=\",1,0 ));\n  }\nelsif ($mode eq \"pdb_temp\
late_test\")\n  {\n    &blast2pdb_template_test ($\
mode,&my_get_opt ( $cl, \"-infile=\",1,1));\n\n  }\
\nelsif ($mode eq \"psi_template_test\")\n  {\n   \
 &psiblast2profile_template_test ($mode,&my_get_op\
t ( $cl, \"-seq=\",1,1,\"-blast=\",1,1));\n\n  }\n\
\nelsif ( $mode eq \"pdb_template\")\n  {\n    &bl\
ast2pdb_template ($mode,&my_get_opt ( $cl, \"-infi\
le=\",1,1, \"-database=\",1,0, \"-method=\",1,0, \\
"-outfile=\",1,0,\"-pdb_type=\",1,0));\n  }\n\nels\
if ( $mode eq \"profile_template\")\n  {\n\n    &p\
siblast2profile_template ($mode,&my_get_opt ( $cl,\
 \"-infile=\",1,1, \"-database=\",1,0, \"-method=\\
",1,0, \"-outfile=\",1,0));\n  }\nelsif ( $mode eq\
 \"psiprofile_template\")\n  {\n    &psiblast2prof\
ile_template ($mode,&my_get_opt ( $cl, \"-infile=\\
",1,1, \"-database=\",1,0, \"-method=\",1,0, \"-ou\
tfile=\",1,0));\n  }\nelsif ( $mode eq \"RNA_templ\
ate\")\n  {\n    &seq2RNA_template ($mode,&my_get_\
opt ( $cl, \"-infile=\",1,1, \"-outfile=\",1,0));\\
n  }\nelsif ( $mode eq \"tm_template\")\n  {\n    \
&seq2tm_template ($mode, \"\", &my_get_opt ( $cl, \
\"-infile=\",1,1,\"-arch=\",1,1,\"-psv=\",1,1, \"-\
outfile=\",1,0,));\n  }\nelsif ( $mode eq \"psitm_\
template\")\n  {\n    &seq2tm_template ($mode,&my_\
get_opt ( $cl, \"-database=\",1,0, \"-infile=\",1,\
1, \"-arch=\",1,1,\"-psv=\",1,1, \"-outfile=\",1,0\
,));\n  }\nelsif ( $mode eq \"ssp_template\")\n  {\
\n    &seq2ssp_template ($mode,&my_get_opt ( $cl, \
\"-infile=\",1,1,\"-seq=\",1,1,\"-obs=\",1,1, \"-o\
utfile=\",1,0));\n  }\nelsif ( $mode eq \"psissp_t\
emplate\")\n  {\n    &seq2ssp_template ($mode,&my_\
get_opt ( $cl, \"-infile=\",1,1,\"-seq=\",1,1,\"-o\
bs=\",1,1, \"-outfile=\",1,0));\n  }\n\nelsif ( $m\
ode eq \"rna_pair\")\n{\n    &seq2rna_pair($mode,&\
my_get_opt ( $cl, \"-pdbfile1=\",1,1, \"-pdbfile2=\
\",1,1, \"-method=\",1,2,\"-param=\",0,0, \"-outfi\
le=\",1,0, ));\n}\nelsif ( $mode eq \"calc_rna_tem\
plate\")\n{\n    &calc_rna_template($mode,&my_get_\
opt ( $cl, \"-infile=\",1,1,\"-pdbfile=\",1,1, \"-\
outfile=\",1,0));\n}\nelse\n  {\n    myexit(flush_\
error( \"$mode is an unknown mode of tc_generic_me\
thod.pl\"));\n  }\nmyexit ($EXIT_SUCCESS);\n\n\nsu\
b seq2ssp_template\n  {\n  my ($mode, $infile,$gor\
_seq,$gor_obs,$outfile)=@_;\n  my %s, %h;\n  my $r\
esult;\n  my (@profiles);\n  &set_temporary_dir (\\
"set\",$infile,\"seq.pep\");\n  %s=read_fasta_seq \
(\"seq.pep\");\n\n\n  open (R, \">result.aln\");\n\
\n  #print stdout \"\\n\";\n  foreach $seq (keys(%\
s))\n    {\n\n      open (F, \">seqfile\");\n     \
 $s{$seq}{seq}=uc$s{$seq}{seq};\n      print (F \"\
>$s{$seq}{name}\\n$s{$seq}{seq}\\n\");\n      clos\
e (F);\n      $lib_name=\"$s{$seq}{name}.ssp\";\n \
     $lib_name=&clean_file_name ($lib_name);\n\n  \
    if ($mode eq \"ssp_template\"){&seq2gor_predic\
tion ($s{$seq}{name},$s{$seq}{seq}, \"seqfile\", $\
lib_name,$gor_seq, $gor_obs);}\n      elsif ($mode\
 eq \"psissp_template\")\n	{\n	  &seq2msa_gor_pred\
iction ($s{$seq}{name},$s{$seq}{seq},\"seqfile\", \
$lib_name,$gor_seq, $gor_obs);\n	}\n\n      if ( !\
-e $lib_name)\n	{\n	  myexit(flush_error(\"GORIV f\
ailed to compute the secondary structure of $s{$se\
q}{name}\"));\n	  myexit ($EXIT_FAILURE);\n	}\n   \
   else\n	{\n	  print stdout \"\\tProcess: >$s{$se\
q}{name} _E_ $lib_name \\n\";\n	  print R \">$s{$s\
eq}{name} _E_ $lib_name\\n\";\n	}\n      unshift (\
@profiles, $lib_name);\n    }\n  close (R);\n  &se\
t_temporary_dir (\"unset\",$mode, $method,\"result\
.aln\",$outfile, @profiles);\n}\n\nsub seq2tm_temp\
late\n  {\n  my ($mode, $db, $infile,$arch,$psv,$o\
utfile)=@_;\n  my %s, %h;\n  my $result;\n  my (@p\
rofiles);\n  &set_temporary_dir (\"set\",$infile,\\
"seq.pep\");\n  %s=read_fasta_seq (\"seq.pep\");\n\
\n\n  open (R, \">result.aln\");\n\n  #print stdou\
t \"\\n\";\n  foreach $seq (keys(%s))\n    {\n    \
  open (F, \">seqfile\");\n      print (F \">$s{$s\
eq}{name}\\n$s{$seq}{seq}\\n\");\n      close (F);\
\n      $lib_name=\"$s{$seq}{name}.tmp\";\n      $\
lib_name=&clean_file_name ($lib_name);\n\n      if\
 ($mode eq \"tm_template\")\n	{\n	  &safe_system (\
\"t_coffee -other_pg fasta_seq2hmmtop_fasta.pl -in\
=seqfile -out=$lib_name -arch=$arch -psv=$psv\");\\
n	}\n      elsif ( $mode eq \"psitm_template\")\n	\
{\n	  &seq2msa_tm_prediction ($s{$seq}{name},$s{$s\
eq}{seq}, $db, \"seqfile\", $lib_name,$arch, $psv)\
;\n	}\n      if ( !-e $lib_name)\n	{\n	  myexit(fl\
ush_error(\"RNAplfold failed to compute the second\
ary structure of $s{$seq}{name}\"));\n	  myexit ($\
EXIT_FAILURE);\n	}\n      else\n	{\n	  print stdou\
t \"\\tProcess: >$s{$seq}{name} _T_ $lib_name\\n\"\
;\n	  print R \">$s{$seq}{name} _T_ $lib_name\\n\"\
;\n	}\n      unshift (@profiles, $lib_name);\n    \
}\n  close (R);\n  &set_temporary_dir (\"unset\",$\
mode, $method,\"result.aln\",$outfile, @profiles);\
\n}\n\nsub seq2RNA_template\n  {\n  my ($mode, $in\
file,$outfile)=@_;\n  my %s, %h, ;\n  my $result;\\
n  my (@profiles);\n  &set_temporary_dir (\"set\",\
$infile,\"seq.pep\");\n  %s=read_fasta_seq (\"seq.\
pep\");\n\n\n  open (R, \">result.aln\");\n\n  #pr\
int stdout \"\\n\";\n  foreach $seq (keys(%s))\n  \
  {\n      open (F, \">seqfile\");\n      print (F\
 \">$s{$seq}{name}\\n$s{$seq}{seq}\\n\");\n      c\
lose (F);\n      $lib_name=\"$s{$seq}{name}.rfold\\
";\n      $lib_name=&clean_file_name ($lib_name);\\
n      &safe_system (\"t_coffee -other_pg RNAplfol\
d2tclib.pl -in=seqfile -out=$lib_name\");\n\n     \
 if ( !-e $lib_name)\n	{\n	 myexit(flush_error(\"R\
NAplfold failed to compute the secondary structure\
 of $s{$seq}{name}\"));\n	  myexit ($EXIT_FAILURE)\
;\n	}\n      else\n	{\n	  print stdout \"\\tProces\
s: >$s{$seq}{name} _F_ $lib_name\\n\";\n	  print R\
 \">$s{$seq}{name} _F_ $lib_name\\n\";\n	}\n      \
unshift (@profiles, $lib_name);\n    }\n  close (R\
);\n  &set_temporary_dir (\"unset\",$mode, $method\
,\"result.aln\",$outfile, @profiles);\n}\nsub psib\
last2profile_template_test\n  {\n  my ($mode, $seq\
,$blast)=@_;\n  my %s, %h, ;\n  my ($result,$psibl\
ast_output,$profile_name,@profiles);\n  my $trim=0\
;\n  my $maxid=100;\n  my $minid=0;\n  my $mincov=\
0;\n  my $maxcov=100;\n\n  %s=read_fasta_seq ($seq\
);\n  open (R, \">result.aln\");\n\n  #print stdou\
t \"\\n\";\n  foreach $seq (keys(%s))\n    {\n\n  \
    open (F, \">seqfile\");\n      print (F \">$A\\
\n$s{$seq}{seq}\\n\");\n      close (F);\n      $p\
siblast_output=$blast;\n      if ( -e $psiblast_ou\
tput)\n	{\n	  %profile=blast_xml2profile($s{$seq}{\
name}, $s{$seq}{seq},$maxid, $minid,$mincov,$psibl\
ast_output);\n\n\n\n	  $profile_name=\"$s{$seq}{na\
me}.prf\";\n	  $profile_name=&clean_file_name ($pr\
ofile_name);\n	  unshift (@profiles, $profile_name\
);\n	  output_profile ($profile_name, \\%profile, \
$trim);\n	  print stdout \"\\tProcess: >$s{$seq}{n\
ame} _R_ $profile_name [$profile{n} Seq.] [$SERVER\
/blast/$db][$CACHE_STATUS]\\n\";\n	  print R \">$s\
{$seq}{name} _R_ $profile_name\\n\";\n	}\n    }\n \
 close (R);\n\n  die;\n}\nsub psiblast2profile_tem\
plate\n  {\n  my ($mode, $infile, $db, $method, $o\
utfile)=@_;\n  my %s, %h, ;\n  my ($result,$psibla\
st_output,$profile_name,@profiles);\n  my $trim=0;\
\n  &set_temporary_dir (\"set\",$infile,\"seq.pep\\
");\n  %s=read_fasta_seq (\"seq.pep\");\n  open (R\
, \">result.aln\");\n\n  #print stdout \"\\n\";\n \
 foreach $seq (keys(%s))\n    {\n      open (F, \"\
>seqfile\");\n      print (F \">$A\\n$s{$seq}{seq}\
\\n\");\n      close (F);\n      $psiblast_output=\
&run_blast ($s{$seq}{name},$method, $db, \"seqfile\
\",\"outfile\");\n\nif ( -e $psiblast_output)\n	{\\
n	  %profile=blast_xml2profile($s{$seq}{name}, $s{\
$seq}{seq},$maxid, $minid,$mincov,$psiblast_output\
);\n	  unlink ($psiblast_output);\n\n	  $profile_n\
ame=\"$s{$seq}{name}.prf\";\n	  $profile_name=&cle\
an_file_name ($profile_name);\n	  unshift (@profil\
es, $profile_name);\n	  output_profile ($profile_n\
ame, \\%profile, $trim);\n	  print stdout \"\\tPro\
cess: >$s{$seq}{name} _R_ $profile_name [$profile{\
n} Seq.] [$SERVER/blast/$db][$CACHE_STATUS]\\n\";\\
n	  print R \">$s{$seq}{name} _R_ $profile_name\\n\
\";\n	}\n    }\n  close (R);\n  &set_temporary_dir\
 (\"unset\",$mode, $method,\"result.aln\",$outfile\
, @profiles);\n}\nsub blast2pdb_template_test\n   \
 {\n      my ($mode,$infile)=@_;\n      my ($maxid\
,$minid,$mincov);\n      $maxid=100;\n      $minid\
=0;\n      $mincov=0;\n\n      print \"$infile\\n\\
";\n\n      %p=blast_xml2profile($s{$seq}{name}, $\
s{$seq}{seq},$maxid, $minid,$mincov,$infile);\n   \
   $c=1;\n      print stdout \"\\tProcess: >$s{$se\
q}{name} [$SERVER/blast/$db][$CACHE_STATUS]\\n\";\\
n      while (!$found && $c<$p{n})\n	{\n	  $pdbid=\
&id2pdbid($p{$c}{identifyer});\n	  if ( length ($p\
dbid)>5){$pdbid=id2pdbid($p{$c}{definition});}\n\n\
	  if ( length ($pdbid)>5)\n	    {\n	      myexit(\
add_error (EXIT_FAILURE,$$,$$,getppid(), \"BLAST_F\
AILURE::Could Not Parse PDBID ($p{$c}{identifyer},\
$p{$c}{definition})\"));\n	    }\n\n\n	  if (!&pdb\
_is_released($pdbid))\n	    {\n	      print stdout\
 \"\\t\\t**$pdbid [PDB NOT RELEASED or WITHDRAWN]\\
\n\";\n	      $c++;\n	    }\n	  elsif (!&pdb_has_r\
ight_type ($pdbid,$type))\n	    {\n	      my $ptyp\
e=&pdb2type ($pdbid);\n	      my $etype=&type2etyp\
e($type);\n\n	      print stdout \"\\t\\t**$pdbid \
[$ptype cannot be used (expected: $etype)]\\n\";\n\
	      $c++;\n	    }\n	  else\n	    {\n	      $fou\
nd=1;\n	    }\n	}\n\n      if ($found)\n	{\n	  pri\
nt stdout \"\\t\\t >$s{$seq}{name} _P_ $pdbid\\n\"\
;\n	}\n      else\n	{\n	  print stdout \"\\t\\t >$\
s{$seq}{name} No Template Selected\\n\";\n	}\n    \
  die;\n    }\nsub blast2pdb_template\n  {\n  my (\
$mode, $infile, $db, $method, $outfile,$type)=@_;\\
n  my %s, %h, ;\n  my ($result,$blast_output);\n  \
&set_temporary_dir (\"set\",$infile,\"seq.pep\");\\
n  %s=read_fasta_seq (\"seq.pep\");\n  open (R, \"\
>result.aln\");\n\n\n  #print stdout \"\\n\";\n  f\
oreach $seq (keys(%s))\n    {\n      my $c;\n     \
 my $found;\n\n      open (F, \">seqfile\");\n    \
  print (F \">$A\\n$s{$seq}{seq}\\n\");\n      clo\
se (F);\n\n      $blast_output=&run_blast ($s{$seq\
}{name},$method, $db, \"seqfile\",\"outfile\");\n\\
n      %p=blast_xml2profile($s{$seq}{name}, $s{$se\
q}{seq},$maxid, $minid,$mincov,$blast_output);\n  \
    unlink ($blast_output);\n\n      $c=1;\n      \
print stdout \"\\tProcess: >$s{$seq}{name} [$SERVE\
R/blast/$db][$CACHE_STATUS]\\n\";\n      while (!$\
found && $c<$p{n})\n	{\n	  $pdbid=&id2pdbid($p{$c}\
{identifyer});\n	  if ( length ($pdbid)>5){$pdbid=\
id2pdbid($p{$c}{definition});}\n\n	  if ( length (\
$pdbid)>5)\n	    {\n	      myexit(add_error (EXIT_\
FAILURE,$$,$$,getppid(), \"BLAST_FAILURE::Could No\
t Parse PDBID ($p{$c}{identifyer},$p{$c}{definitio\
n})\"));\n	    }\n\n\n	  if (!&pdb_is_released($pd\
bid))\n	    {\n	      print stdout \"\\t\\t**$pdbi\
d [PDB NOT RELEASED or WITHDRAWN]\\n\";\n	      $c\
++;\n	    }\n	  elsif (!&pdb_has_right_type ($pdbi\
d,$type))\n	    {\n	      my $ptype=&pdb2type ($pd\
bid);\n	      my $etype=&type2etype($type);\n\n	  \
    print stdout \"\\t\\t**$pdbid [$ptype cannot b\
e used (expected: $etype)]\\n\";\n	      $c++;\n	 \
   }\n	  else\n	    {\n	      $found=1;\n	    }\n	\
}\n\n      if ($found)\n	{\n	  print R \">$s{$seq}\
{name} _P_ $pdbid\\n\";\n	  print stdout \"\\t\\t \
>$s{$seq}{name} _P_ $pdbid\\n\";\n	}\n      else\n\
	{\n	  print R \">$s{$seq}{name}\\n\";\n	  print s\
tdout \"\\t\\t >$s{$seq}{name} No Template Selecte\
d\\n\";\n	}\n    }\n  close (R);\n  &set_temporary\
_dir (\"unset\",$mode, $method,\"result.aln\",$out\
file);\n}\nsub type2etype\n  {\n    my $type=shift\
;\n    my $etype;\n\n    if ( $type=~/n/){$etype.=\
\"NMR \";}\n    if ( $type=~/d/){$etype.=\"diffrac\
tion \";}\n    if ( $type=~/m/){$etype.=\"model \"\
;}\n    return $etype;\n  }\nsub pdb2type\n  {\n  \
   my $pdb=shift;\n     my $f=vtmpnam();\n\n     m\
y $value= &safe_system (\"t_coffee -other_pg extra\
ct_from_pdb -model_type $pdb > $f\");\n     my $r=\
&file2string ($f);\n     chomp($r);\n     return $\
r;\n   }\nsub pdb_has_right_type\n  {\n    my $pdb\
=shift;\n    my $type=shift;\n\n    my $f=vtmpnam(\
);\n\n    my $value= &safe_system (\"t_coffee -oth\
er_pg extract_from_pdb -model_type $pdb > $f\");\n\
    my $r=&file2string ($f);\n    chomp($r);\n\n\n\
    if ( $r eq \"NMR\" && $type=~/n/){return 1;}\n\
    elsif ( $r eq \"diffraction\" && $type=~/d/){r\
eturn 1;}\n    elsif ( $r eq \"model\" && $type=~/\
m/){return 1;}\n    else {return 0;}\n  }\nsub pdb\
_is_released\n  {\n    my $pdb=shift;\n    my $f=v\
tmpnam();\n\n    $value= &safe_system (\"t_coffee \
-other_pg extract_from_pdb -is_released_pdb_name $\
pdb > $f\");\n    my $r=&file2string ($f);\n    ch\
omp($r);\n    return $r;\n  }\nsub blast_msa\n  {\\
n    my ($blast,$infile,$db,$outfile)=@_;\n    my \
($a, %s1, %s, %qs, %qs1);\n    my $seqfile;\n    m\
y $SEQ=new FileHandle;\n    my $seqfile=\"seqfile\\
";\n    my @txt;\n\n\n    %s1=&read_fasta_seq ($db\
);\n    %s=&fasta_hash2index_hash(%s1);\n    %qs1=\
&read_fasta_seq ($infile);\n    %qs=&fasta_hash2in\
dex_hash(%qs1);\n\n\n    #&safe_system (\"formatdb\
 -i $db\");\n    if ($blast eq \"blastp\"){&safe_s\
ystem  (\"blastall -i $infile -d $db -m7 -p blastp\
 -o io\");}\n    elsif ($blast eq \"blastn\"){&saf\
e_system  (\"blastn -query $infile -db $db -outfmt\
 5 -word_size 4 -out io\");}\n\n    &set_blast_typ\
e (\"io\");\n\n\n    my %FB=&xml2tag_list (\"io\",\
 \"Iteration\");\n    open (F, \">$outfile\");\n  \
  print F \"! TC_LIB_FORMAT_01\\n\";\n    print F \
\"$s{n}\\n\";\n    for ( my $a=0; $a<$s{n}; $a++)\\
n      {\n	print F \"$s{$a}{name} $s{$a}{len} $s{$\
a}{seq}\\n\";\n      }\n\n\n    for ( my $a=0; $a<\
$FB{n}; $a++)\n      {\n	my %p=blast_xml2profile (\
$qs{$a}{name}, $qs{$a}{seq},100, 0, 0, $FB{$a}{bod\
y});\n	my $query=$p{0}{name};\n	my $i= $s1{$query}\
{order}+1;\n	for (my $b=1; $b<$p{n}; $b++)\n	  {\n\
	    my $l=length ($p{$b}{Qseq});\n	    my $hit=$p\
{$b}{definition};\n	    my $Qstart=$p{$b}{Qstart};\
\n	    my $Hstart=$p{$b}{Hstart};\n	    my $identi\
ty=$p{$b}{identity};\n	    my @lrQ=split (//,$p{$b\
}{Qseq});\n	    my @lrH=split (//,$p{$b}{Hseq});\n\
\n	    my $j= $s1{$hit}{order}+1;\n	    #if ( $j==\
$i){next;}\n	    printf F \"# %d %d\\n\", $i, $j;\\
n	    #  print  F \"\\n$p{$b}{Qseq} ($Qstart)\\n$p\
{$b}{Hseq} ($Hstart)\";\n	    for ($c=0; $c<$l; $c\
++)\n	      {\n		my $rQ=$lrQ[$c];\n		my $rH=$lrH[$\
c];\n		my $n=0;\n\n		if ($rQ ne \"-\"){$n++, $Qsta\
rt++;}\n		if ($rH ne \"-\"){$n++; $Hstart++;}\n\n	\
	if ( $n==2)\n		  {\n		    printf F \"\\t%d %d %d\\
\n\", $Qstart-1, $Hstart-1,$identity;\n		  }\n	   \
   }\n	  }\n      }\n    print F \"! SEQ_1_TO_N\\n\
\";\n    close (F);\n    return $output;\n  }\n\ns\
ub blast_msa_old\n  {\n    my ($infile,$outfile)=@\
_;\n    my ($a, %seq);\n    %s1=&read_fasta_seq ($\
infile);\n    foreach $s (keys (%s1))\n      {\n	$\
i=$s1{$s}{order};\n	$s{$i}{name}=$s;\n	$s{$i}{seq}\
=$s1{$s}{seq};\n	$s{$i}{len}=length( $s{$i}{seq});\
\n	$s{n}++;\n      }\n    &safe_system (\"formatdb\
 -i $infile\");\n    &safe_system (\"blastall -i $\
infile -d $infile -m7 -o io\");\n    &set_blast_ty\
pe (\"io\");\n\n    %FB=&xml2tag_list (\"io\", \"I\
teration\");\n\n    open (F, \">$outfile\");\n    \
print F \"! TC_LIB_FORMAT_01\\n\";\n    print F \"\
$s{n}\\n\";\n    for ( $a=0; $a<$s{n}; $a++)\n    \
  {\n	print F \"$s{$a}{name} $s{$a}{len} $s{$a}{se\
q}\\n\";\n      }\n    for ( $a=0; $a<$FB{n}; $a++\
)\n      {\n	%p=blast_xml2profile ($s{$a}{name}, $\
s{$a}{seq},100, 0, 0, $FB{$a}{body});\n	for ($b=1;\
 $b<$p{n}; $b++)\n	  {\n	    my $l=length ($p{$b}{\
Qseq});\n	    my $hit=$p{$b}{definition};\n	    my\
 $Qstart=$p{$b}{Qstart};\n	    my $Hstart=$p{$b}{H\
start};\n	    my $identity=$p{$b}{identity};\n	   \
 my @lrQ=split (//,$p{$b}{Qseq});\n	    my @lrH=sp\
lit (//,$p{$b}{Hseq});\n	    my $i= $s1{$s{$a}{nam\
e}}{order}+1;\n	    my $j= $s1{$hit}{order}+1;\n	 \
   #if ( $j==$i){next;}\n	    printf F \"# %d %d\\\
n\", $i, $j;\n	    #  print  F \"\\n$p{$b}{Qseq} (\
$Qstart)\\n$p{$b}{Hseq} ($Hstart)\";\n	    for ($c\
=0; $c<$l; $c++)\n	      {\n		my $rQ=$lrQ[$c];\n		\
my $rH=$lrH[$c];\n		my $n=0;\n\n		if ($rQ ne \"-\"\
){$n++, $Qstart++;}\n		if ($rH ne \"-\"){$n++; $Hs\
tart++;}\n\n		if ( $n==2)\n		  {\n		    printf F \\
"\\t%d %d %d\\n\", $Qstart-1, $Hstart-1,$identity;\
\n		  }\n	      }\n	  }\n      }\n    print F \"! \
SEQ_1_TO_N\\n\";\n    close (F);\n    return $outp\
ut;\n\n  }\n\nsub seq2msa\n  {\n    my ($mode, $in\
file, $method, $param, $outfile,$database)=@_;\n  \
  &set_temporary_dir (\"set\",$infile,\"seq.pep\",\
 $database, \"db.pep\");\n    $param.=\" >/dev/nul\
l 2>&1 \";\n\n\n    #make sure test.pep is in FAST\
A\n    &safe_system (\"t_coffee -other_pg seq_refo\
rmat -in seq.pep -output fasta_seq > x\");\n    `m\
v x seq.pep`;\n\n    if ( $method eq \"blastp\")\n\
      {\n	&blast_msa (\"blastp\",\"seq.pep\",$data\
base,\"result.aln\");\n      }\n    elsif ( $metho\
d eq \"blastn\")\n      {\n	&blast_msa (\"blastn\"\
,\"seq.pep\",$database,\"result.aln\");\n      }\n\
\n    elsif ( $method eq \"muscle\")\n      {\n	`m\
uscle -in seq.pep -out result.aln $param`;\n      \
}\n    elsif ( $method eq \"probcons\")\n      {\n\
	`probcons seq.pep >result.aln 2>/dev/null`;\n    \
  }\n    elsif ( $method eq \"mafft\")\n      {\n	\
`mafft --quiet --localpair --maxiterate 1000 seq.p\
ep> result.aln  2>/dev/null`\n      }\n    elsif (\
 $method=~/prank/)\n      {\n	`$method -d=seq.pep \
-o=result.aln -quiet 2>/dev/null`;\n	`mv result.al\
n.1.fas result.aln`;\n      }\n    elsif ($method \
eq \"clustalo\")\n      {\n	`clustalo -i seq.pep >\
 result.aln`;\n      }\n    else\n      {\n	`$meth\
od -infile=seq.pep -outfile=result.aln`;\n      }\\
n\n    &set_temporary_dir (\"unset\",$mode, $metho\
d,\"result.aln\",$outfile);\n    myexit ($EXIT_SUC\
CESS);\n  }\n\nsub seq2thread_pair\n  {\n    my ($\
mode, $infile, $pdbfile1, $method, $param, $outfil\
e)=@_;\n    &set_temporary_dir (\"set\",$infile,\"\
seq.pep\",$pdbfile1,\"struc.pdb\");\n    if ($meth\
od eq \"fugueali\")\n      {\n	#Env Variable that \
need to be defined for Fugue\n	if (!$ENV{FUGUE_LIB\
_LIST}){$ENV{FUGUE_LIB_LIST}=\"DUMMY\";}\n	if (!$E\
NV{HOMSTRAD_PATH})  {$ENV{HOMSTRAD_PATH}=\"DUMMY\"\
;}\n	if (!$ENV{HOMS_PATH}){$ENV{HOMS_PATH}=\"DUMMY\
\";}\n\n	`joy struc.pdb >x 2>x`;\n	&check_file(\"s\
truc.tem\", \"Joy failed [FATAL:$PROGRAM/$method]\\
");\n	`melody -t struc.tem >x 2>x`;\n	&check_file(\
\"struc.tem\", \"Melody failed [FATAL:$PROGRAM/$me\
thod]\");\n	`fugueali -seq seq.pep -prf struc.fug \
-print > tmp_result.aln`;\n\n	&check_file(\"tmp_re\
sult.aln\", \"Fugue failed [FATAL:$PROGRAM/$method\
]\");\n	&safe_system (\"t_coffee -other_pg seq_ref\
ormat -in tmp_result.aln -output fasta_aln >result\
.aln\");\n      }\n    elsif ( $method eq \"t_coff\
ee\")\n      {\n	&safe_system (\"t_coffee -in Pstr\
uc.pdb Sseq.pep Mslow_pair -outfile result.aln -qu\
iet\");\n      }\n    else\n      {\n	&safe_system\
 (\"$method -infile=seq.pep -pdbfile1=struc.pdb -o\
utfile=result.aln $param>x 2>x\");\n      }\n    &\
set_temporary_dir (\"unset\",$mode,$method,\"resul\
t.aln\",$outfile);\n    myexit ($EXIT_SUCCESS);\n \
 }\nsub seq2pdbid_pair\n  {\n    my ($mode, $pdbfi\
le1, $pdbfile2, $method, $param, $outfile)=@_;\n  \
  my ($name);\n\n\n    &set_temporary_dir (\"set\"\
);\n    $name=$pdbfile1.\" \".$pdbfile2;\n\n    if\
 (    &cache_file(\"GET\",\"\",\"$name\",\"$method\
\",\"dali\",$outfile,\"EBI\"))\n      {return $out\
file;}\n    else\n      {\n	if ($method eq \"daliw\
eb\")\n	  {\n	    $pdbfile1=~/(....)(.)/;\n	    $i\
d1=$1; $c1=$2;\n\n	    $pdbfile2=~/(....)(.)/;\n	 \
   $id2=$1; $c2=$2;\n\n	    $command=\"t_coffee -o\
ther_pg dalilite.pl --pdb1 $id1 --chainid1 $c1 --p\
db2 $id2 --chainid2 $c2 --email=$EMAIL  >dali_stde\
rr 2>dali_stderr\";\n	    $dali=`$command`;\n\n	  \
  open (F, \"dali_stderr\");\n	    while (<F>)\n	 \
     {\n		if ( /JobId: dalilite-(\\S+)/)\n		{\n		 \
 $jobid=$1;\n		}\n	      }\n	    close (F);\n	    \
unlink (\"dali_stderr\");\n\n	    $output1=\"dalil\
ite-$jobid.txt\";\n	    if ( -e $output1)\n	      \
{\n		unlink ($output1);\n		&url2file (\"http://www\
.ebi.ac.uk/Tools/es/cgi-bin/jobresults.cgi/dalilit\
e/dalilite-$jobid/aln.html\", \"output2\");\n\n		i\
f ( -e \"output2\")\n		  {\n		    my ($seq1, $seq2\
);\n		    $seq1=$seq2=\"\";\n\n		    open (F, \"ou\
tput2\");\n		    while (<F>)\n		      {\n			$l=$_;\
\n			if ( $l=~/Query\\s+(\\S+)/)\n			  {\n			    $\
seq1.=$1;\n			  }\n			elsif ( $l=~/Sbjct\\s+(\\S+)\
/)\n			  {\n			    $seq2.=$1;\n			  }\n		      }\n\
		    close (F);\n		    unlink (\"output2\");\n		 \
   if ($seq1 ne \"\" && $seq2 ne \"\")\n		      {\\
n			$output3=\">$A\\n$seq1\\n>$B\\n$seq2\\n\";\n		\
	$output3=~s/\\./-/g;\n			open (F, \">result.aln\"\
);\n			print F \"$output3\";\n			close (F);\n		   \
   }\n		  }\n	      }\n	  }\n      }\n    &cache_f\
ile(\"SET\",\"\",\"$name\",\"$method\",\"dali\",\"\
result.aln\",\"EBI\");\n    &set_temporary_dir (\"\
unset\",$mode, $method, \"result.aln\",$outfile);\\
n    myexit ($EXIT_SUCCESS);\n  }\nsub seq2pdb_pai\
r\n  {\n    my ($mode, $pdbfile1, $pdbfile2, $meth\
od, $param, $outfile)=@_;\n\n    &set_temporary_di\
r (\"set\",$pdbfile1,\"pdb1.pdb\",$pdbfile2,\"pdb2\
.pdb\");\n    if ($method eq \"t_coffee\")\n      \
{\n	&safe_system (\"t_coffee -in Ppdb1.pdb Ppdb2.p\
db -quiet -outfile=result.aln\");\n      }\n    el\
sif ( $method eq \"DaliLite\")\n      {\n	if ( &sa\
fe_system (\"DaliLite -pairwise pdb1.pdb pdb2.pdb \
>tmp1\")==$EXIT_SUCCESS)\n	  {\n	     my ($seq1, $\
seq2);\n	     $seq1=$seq2=\"\";\n\n	     open (F, \
\"tmp1\");\n	     while (<F>)\n	       {\n		 $l=$_\
;\n		 if ( $l=~/Query\\s+(\\S+)/)\n		   {\n		     \
$seq1.=$1;\n		   }\n		 elsif ( $l=~/Sbjct\\s+(\\S+\
)/)\n		   {\n		     $seq2.=$1;\n		   }\n	       }\\
n	     close (F);\n	     unlink (\"tmp1\");\n	    \
 if ($seq1 ne \"\" && $seq2 ne \"\")\n	       {\n	\
	 my $output3=\">$A\\n$seq1\\n>$B\\n$seq2\\n\";\n	\
	 $output3=~s/\\./-/g;\n		 open (F, \">result.aln\\
");\n		 print F \"$output3\";\n		 close (F);\n	   \
    }\n	   }\n	else\n	  {\n	    print \"ERROR: Dal\
Lite failed to align the considered structures[tc_\
generic_method.pl]\\n\";\n	  }\n      }\n    elsif\
 ( $method eq \"TMalign\")\n      {\n	if ( &safe_s\
ystem (\"TMalign pdb1.pdb pdb2.pdb >tmp1\")==$EXIT\
_SUCCESS)\n	  {\n	    `tail -4 tmp1 > tmp2`;\n\n	 \
   open (F, \"tmp2\");\n	    while (<F>)\n	      {\
\n		unshift(@l, $_);\n	      }\n	    close (F);\n	\
    open (F, \">result.aln\");\n	    $l[3]=~s/[^a-\
zA-Z0-9-]/\\-/g;\n	    $l[1]=~s/[^a-zA-Z0-9-]/\\-/\
g;\n	    print F \">$A\\n$l[3]\\n>$B\\n$l[1]\\n\";\
\n	    close (F);\n	  }\n	else\n	  {\n	    print \\
"ERROR: TMalign failed to align the considered str\
uctures[tc_generic_method.pl]\\n\";\n	    `rm resu\
lt.aln >/dev/null 2>/dev/null`;\n	  }\n      }\n  \
  elsif ( $method eq \"mustang\")\n      {\n	if ( \
&safe_system (\"mustang -i pdb1.pdb pdb2.pdb -F fa\
sta >/dev/null 2>/dev/null\")==$EXIT_SUCCESS)\n	  \
{\n	    `mv results.afasta result.aln`;\n	  }\n	el\
se\n	  {\n	    print \"ERROR: mustang failed to al\
ign the considered structures[tc_generic_method.pl\
]\\n\";\n	    `rm result.aln >/dev/null 2>/dev/nul\
l`;\n	  }\n      }\n    else\n      {\n	if ( &safe\
_system (\"$method -pdbfile1=pdb1.pep -pdbfile2=pd\
b2.pdb -outfile=result.aln $param>x 2>x\")==$EXIT_\
SUCCESS)\n	  {\n	    `mv results.afasta result.aln\
`;\n	  }\n	else\n	  {\n	    print \"ERROR: $method\
 failed to align the considered structures[tc_gene\
ric_method.pl]\\n\";\n	    `rm result.aln >/dev/nu\
ll 2>/dev/null`;\n	  }\n      }\n    &set_temporar\
y_dir (\"unset\",$mode, $method, \"result.aln\",$o\
utfile);\n    myexit ($EXIT_SUCCESS);\n  }\n\nsub \
seq2profile_pair\n{\n	my ($mode, $profile1, $profi\
le2, $method, $param, $outfile)=@_;\n\n\n	if ($met\
hod eq \"clustalw\")\n	{\n		&set_temporary_dir (\"\
set\",$profile1,\"prf1.aln\",$profile2,\"prf2.aln\\
");\n		`clustalw -profile1=prf1.aln -profile2=prf2\
.aln -outfile=result.aln`;\n		&set_temporary_dir (\
\"unset\",$mode, $method, \"result.aln\",$outfile)\
;\n	}\n	elsif ( $method eq \"clustalo\")\n	{\n		`c\
lustalo --p1 $profile1 --p2 $profile2 -o $outfile \
--force`;\n	}\n	elsif ( $method eq \"hhalign\")\n	\
{\n		hhalign ( $profile1,$profile2,$outfile,$param\
);\n	}\n	else\n	{\n		`$method -profile1=prf1.aln -\
profile2=prf2.aln -outfile=result.aln $param>x 2>x\
`;\n	}\n	myexit ($EXIT_SUCCESS);\n}\n\nsub pg_is_i\
nstalled\n  {\n    my @ml=@_;\n    my ($r, $p, $m)\
;\n    my $supported=0;\n\n    my $p=shift (@ml);\\
n    if ($p=~/::/)\n      {\n	if (safe_system (\"p\
erl -M$p -e 1\")==$EXIT_SUCCESS){return 1;}\n	else\
 {return 0;}\n      }\n    else\n      {\n	$r=`whi\
ch $p 2>/dev/null`;\n	if ($r eq \"\"){$r=0;}\n	els\
e {$r=1;}\n\n	if ($r==0 && is_blast_package ($p)){\
return pg_is_installed (\"legacy_blast.pl\");}\n	e\
lse {return $r;}\n      }\n  }\n\nsub is_blast_pac\
kage\n  {\n    my $p=shift;\n    if ( $p=~/blastp/\
){return 1;}\n    elsif ($p=~/blastall/){return 1;\
}\n    elsif ($p=~/blastn/){return 1;}\n    elsif \
($p=~/blastx/){return 1;}\n    elsif ($p=~/formatd\
b/){return 1;}\n    else {return 0;}\n  }\n\nsub c\
heck_internet_connection\n  {\n    my $internet;\n\
    my $tmp;\n    &check_configuration ( \"wget\")\
;\n\n    $tmp=&vtmpnam ();\n\n    if     (&pg_is_i\
nstalled    (\"wget\")){`wget www.google.com -O$tm\
p >/dev/null 2>/dev/null`;}\n    elsif  (&pg_is_in\
stalled    (\"curl\")){`curl www.google.com -o$tmp\
 >/dev/null 2>/dev/null`;}\n\n    if ( !-e $tmp ||\
 -s $tmp < 10){$internet=0;}\n    else {$internet=\
1;}\n    if (-e $tmp){unlink $tmp;}\n\n    return \
$internet;\n  }\nsub check_pg_is_installed\n  {\n \
   my @ml=@_;\n    my $r=&pg_is_installed (@ml);\n\
    if (!$r && $p=~/::/)\n      {\n	print STDERR \\
"\\nYou Must Install the perl package $p on your s\
ystem.\\nRUN:\\n\\tsudo perl -MCPAN -e 'install $p\
g'\\n\";\n      }\n    elsif (!$r)\n      {\n	myex\
it(flush_error(\"\\nProgram $p Supported but Not I\
nstalled on your system\"));\n      }\n    else\n \
     {\n	return 1;\n      }\n  }\nsub set_temporar\
y_dir\n  {\n    my @list=@_;\n    my $dir_mode, $a\
, $mode, $method;\n\n    $dir_mode=shift (@list);\\
n\n\n    if ( $dir_mode eq \"set\")\n      {\n	$in\
itial_dir=cwd();\n	if ( !$tmp_dir)\n	  {\n	    $ra\
nd=rand (100000);\n	    $tmp_dir=\"$TMPDIR/tmp4tco\
ffee_profile_pair_dir_$$\\_P_$rand\";\n	  }\n	if (\
 !-d $tmp_dir)\n	  {\n	    push (@TMPDIR_LIST, $tm\
p_dir);\n	    `mkdir $tmp_dir`;\n	  }\n\n	for ( $a\
=0; $a<=$#list; $a+=2)\n	      {\n		if (-e $list[$\
a]){ `cp $list[$a] $tmp_dir/$list[$a+1]`;}\n	     \
 }\n	chdir $tmp_dir;\n      }\n    elsif ( $dir_mo\
de eq \"unset\")\n      {\n	$mode=shift (@list);\n\
	$method=shift (@list);\n\n	if (!-e $list[0])\n	  \
{\n	   myexit(flush_error(\"Program $method failed\
 to produce $list[1]\" ));\n	    myexit ($EXIT_FAI\
LURE);\n	  }\n	else\n	  {\n	    chdir $initial_dir\
;\n	    # `t_coffee -other_pg seq_reformat -in $tm\
p_dir/$list[0] -output fasta_aln -out $tmp_dir/res\
ult2.aln`;\n	    `cp $tmp_dir/$list[0] $tmp_dir/re\
sult2.aln`;\n	    if ( $list[1] eq \"stdout\")\n	 \
     {\n		open (F, \"$tmp_dir/result2.aln\");\n		w\
hile (<F>){print $_;}close(F);\n	      }\n	    els\
e\n	      {\n		`mv $tmp_dir/result2.aln $list[1]`;\
\n	      }\n	    shift (@list); shift (@list);\n	 \
   foreach $f (@list)\n	      {\n		if (-e (\"$tmp_\
dir/$f\")){`mv $tmp_dir/$f .`;}\n	      }\n	  }\n \
     }\n  }\n\n\n\n\nsub my_get_opt\n  {\n    my @\
list=@_;\n    my $cl, $a, $argv, @argl;\n\n    @ar\
gl=();\n    $cl=shift @list;\n    for ( $a=0; $a<=\
$#list; $a+=3)\n      {\n	$option=$list[$a];\n	$op\
tional=$list[$a+1];\n	$status=$list[$a+2];\n	$argv\
=\"\";\n	if ($cl=~/$option(\\S+)/){$argv=$1;}\n	@a\
rgl=(@argl,$argv);\n\n\n	#$optional:0=>optional\n	\
#$optional:1=>must be set\n	#$status: 0=>no requir\
ement\n	#$status: 1=>must be an existing file\n	#$\
status: 2=>must be an installed package\n\n\n	if (\
$optional==0){;}\n	elsif ( $optional==1 && $argv e\
q \"\")\n	  {\n	    myexit(flush_error( \"ERROR: O\
ption $option must be set\"));\n	    myexit ($EXIT\
_FAILURE);\n	  }\n	if ($status==0){;}\n	elsif ($st\
atus ==1 && $argv ne \"\" && !-e $argv)\n	  {\n	  \
  myexit(flush_error( \"File $argv must exist\"));\
\n	    myexit ($EXIT_FAILURE);\n	  }\n	elsif ( $st\
atus==2 && $argv ne \"\" && &check_pg_is_installed\
 ($argv)==0)\n	  {\n	    myexit(flush_error( \" $a\
rgv is not installed\"));\n	    myexit ($EXIT_FAIL\
URE);\n	  }\n      }\n\n    return @argl;\n    }\n\
\nsub check_file\n  {\n    my ($file, $msg)=@_;\n\\
n    if ( !-e $file)\n      {\n	myexit(flush_error\
(\"$msg\"));\n      }\n    }\nsub hhalign\n  {\n  \
  my ($aln1, $aln2, $outfile, $param)=@_;\n    my \
$h1, $h2;\n\n    $h{0}{index}=0;\n    $h{1}{index}\
=1;\n\n    $h{0}{aln}=$aln1;\n    $h{1}{aln}=$aln2\
;\n\n\n\n    %{$h{0}}=aln2psi_profile (%{$h{0}});\\
n    %{$h{1}}=aln2psi_profile (%{$h{1}});\n\n    $\
param=~s/#S/ /g;\n    $param=~s/#M/\\-/g;\n    $pa\
ram=~s/#E/\\=/g;\n\n\n\n    $command=\"hhalign -i \
$h{0}{a3m} -t $h{1}{a3m} -tc $outfile.tmp -rank 1 \
-mapt 0 $param\";\n    `$command`;\n\n  #  `hhalig\
n -i $h{0}{a3m} -t $h{1}{a3m} -tc $outfile.tmp -ra\
nk 1 -mapt 0 -gapf 0.8 -gapg 0.8`;\n\n\n    # To r\
un global use the following\n\n    open (I, \"$out\
file.tmp\");\n    open (O, \">$outfile\");\n    $h\
{0}{cons}=s/\\./x/g;\n    $h{1}{cons}=s/\\./x/g;\n\
\n    print O \"! TC_LIB_FORMAT_01\\n2\\n$h{0}{nam\
e} $h{0}{len} $h{0}{seq}\\n$h{1}{name} $h{1}{len} \
$h{1}{seq}\\n#1 2\\n\";\n\n    while (<I>)\n      \
{\n	if (/(\\d+)\\s+(\\d+)\\s+(\\d+)/)\n	  {\n	    \
print O \"\\t$h{0}{$1}\\t$h{1}{$2}\\t$3\\n\";\n	  \
}\n      }\n    print O \"! SEQ_1_TO_N\\n\";\n\n  \
  close (O);\n    close (I);\n  }\n\nsub aln2psi_p\
rofile\n  {\n    my (%h)=@_;\n    my ($aln,$i,$hv,\
 $a, @c, $n);\n\n\n    $i=$h{index};\n    $aln=$h{\
aln};\n\n    `cp $aln $$.hhh_aln`;\n    $command=\\
"t_coffee -other_pg seq_reformat -in $aln -output \
hasch\";\n    $hv=`$command`;chomp ($hv);\n\n    $\
h{a2m}=\"$tmp/$hv.tmp4hhpred.a2m\";\n    $h{a3m}=\\
"$tmp/$hv.tmp4hhpred.a3m\";\n    if ( -e $h{a3m}){\
;}\n    else\n      {\n	$x=`which hhconsensus`;\n	\
`hhconsensus  -M 50 -i $h{aln} -oa2m $h{a2m}`;\n	i\
f (!-e $h{a2m})\n	  {\n	    print STDERR \"Program\
 tc_generic_method.pl FAILED to run:\\n\\thhconsen\
sus  -M 50 -i $h{aln} -oa2m $h{a2m}\";\n	    myexi\
t ($EXIT_FAILURE);\n	  }\n\n	`hhconsensus  -M 50 -\
i $h{aln} -oa3m $h{a3m}`;\n	if (!-e $h{a3m})\n	  {\
\n	    print STDERR \"Program tc_generic_method.pl\
 FAILED to run:\\n\\thhconsensus  -M 50 -i $h{aln}\
 -oa3m $h{a3m}\";\n	    myexit ($EXIT_FAILURE);\n	\
  }\n       `buildali.pl $h{a3m} -n 1`;\n      }\n\
\n\n    $h{a2m_seq}=`head -n 2 $h{a2m} | grep -v \\
">\"`;chomp ($h{a2m_seq});\n    $h{a3m_seq}=`head \
-n 2 $h{a3m} | grep -v \">\"`;chomp ($h{a3m_seq});\
\n    $h{cons}=$h{a2m_seq};\n    $h{seq}=`head -n \
2 $h{aln} | grep -v \">\"`;chomp ($h{seq});\n\n\n\\
n    @c=split (//, $h{cons});\n    $h{len}=$#c+1;\\
n    for ($n=0,$a=0, $b=0; $a<$h{len};$a++)\n     \
 {\n	if ( $c[$a]=~/[A-Z]/)\n	  {\n	    $h{++$n}=++\
$b;\n\n	  }\n	elsif ( $c[$a]=~/[a-z\\.]/)\n	  {\n	\
    ++$b;\n	  }\n      }\n\n    $name=`head -n 2 $\
h{aln} | grep \">\"`;\n    $name=~/\\>(\\S+)/;\n  \
  $h{name}=$1;\n\n    `cp $h{a2m} $i.a2m`;\n    `c\
p $h{a3m} $i.a3m`;\n    `cp $h{aln} $i.hh_aln`;\n\\
n    return %h;\n  }\n\nsub read_fasta_seq\n  {\n \
   my $f=@_[0];\n    my %hseq;\n    my (@seq, @com\
, @name);\n    my ($a, $s,$nseq);\n\n    open (F, \
$f);\n    while (<F>)\n      {\n	$s.=$_;\n      }\\
n    close (F);\n\n\n    @name=($s=~/>(\\S*).*\\n[\
^>]*/g);\n\n    @seq =($s=~/>.*.*\\n([^>]*)/g);\n \
   @com =($s=~/>\\S*(.*)\\n([^>]*)/g);\n\n\n    $n\
seq=$#name+1;\n\n    for ($a=0; $a<$nseq; $a++)\n \
     {\n	my $s;\n	my $n=$name[$a];\n	$hseq{$n}{nam\
e}=$n;\n	$seq[$a]=~s/[^A-Za-z]//g;\n	$hseq{$n}{ord\
er}=$a;\n	$hseq{$n}{seq}=$seq[$a];\n	$hseq{$n}{com\
}=$com[$a];\n\n      }\n    return %hseq;\n  }\n\n\
\nsub read_fasta_aln\n  {\n    my $f=@_[0];\n    m\
y %hseq;\n    my (@seq, @com, @name);\n    my ($a,\
 $s,$nseq);\n\n    open (F, $f);\n    while (<F>)\\
n      {\n	$s.=$_;\n      }\n    close (F);\n\n\n \
   @name=($s=~/>(\\S*).*\\n[^>]*/g);\n\n    @seq =\
($s=~/>.*.*\\n([^>]*)/g);\n    @com =($s=~/>\\S*(.\
*)\\n([^>]*)/g);\n\n\n    $nseq=$#name+1;\n\n    f\
or ($a=0; $a<$nseq; $a++)\n      {\n	my $s;\n	my $\
n=$name[$a];\n	$hseq{$n}{name}=$n;\n	$seq[$a]=~s/[\
^A-Za-z-]//g;\n	$hseq{$n}{order}=$a;\n	$hseq{$n}{s\
eq}=$seq[$a];\n	$hseq{$n}{com}=$com[$a];\n\n      \
}\n    return %hseq;\n  }\n\nsub recode_name2\n{\n\
	my ($in)=shift;\n	my $mode=shift;\n\n	my %seq;\n	\
my $new_name;\n\n	if (! -e $in){return;}\n\n	#need\
ed by ClustalOmega to avoid very long names\n	open\
 (INFILE, \"+<$in\");\n\n	my $line;\n\n	if ($mode \
eq \"code\")\n	{\n		chomp($line = <INFILE>);\n		my\
 $line_length = length($line);\n		$new_name=++$REC\
ODE_N;\n		$new_name=\">$new_name\";\n		my $new_len\
gth = length($new_name);\n		$RECODE {$new_name}=$l\
ine;\n		for ($count = $new_length; $count < $line_\
length; $count++)\n		{\n			$new_name .= \" \";\n		\
}\n		$new_name=\"$new_name\\n\";\n		seek INFILE, 0\
, 0\n			or die \"could not seek: $!\";\n		print IN\
FILE \"$new_name\";\n	}\n	else\n	{\n		my $n_found \
= 0;\n		my $file_pos=0;\n		$file_pos=tell INFILE;\\
n		while (<INFILE>)\n		{\n			$line=$_;\n			$line =\
~ s/\\s*$//;\n\n			$old_name= $RECODE{$line};\n			\
if ($old_name ne \"\")\n			{\n				seek INFILE, $fi\
le_pos, 0\n					or die \"could not seek: $!\";\n		\
		print INFILE \"$old_name\\n\";\n				$file_pos++;\
\n				if ($file_pos == 2)\n				{\n					print \"sto\
p\\n\";\n					break;\n				}\n			}\n			$file_pos=te\
ll INFILE;\n		}\n\n	}\n\n\n	close INFILE;\n}\n\n\n\
sub recode_name\n{\n	my ($in)=shift;\n	my $mode=sh\
ift;\n	my $f=new FileHandle;\n	my %seq;\n	my $new_\
name;\n\n	if (! -e $in){return;}\n\n	#needed by Cl\
ustalOmega to avoid very long names\n	%seq=read_fa\
sta_aln ($in);\n\n	open ($f, \">$in\");\n	foreach \
my $s (keys(%seq))\n	{\n		if ($mode eq \"code\")\n\
		{\n			$new_name=++$RECODE_N;\n			$RECODE {$new_n\
ame}=$seq{$s}{name};\n		}\n		else\n		{\n			$new_na\
me=$RECODE{$seq{$s}{name}};\n		}\n		print $f \">$n\
ew_name\\n$seq{$s}{seq}\\n\";\n	}\n	close $f;\n}\n\
\nsub fasta_hash2index_hash\n  {\n    my %s1=@_;\n\
    my %s;\n    foreach my $s (keys (%s1))\n      \
{\n	my $i=$s1{$s}{order};\n	$s{$i}{name}=$s;\n	$s{\
$i}{seq}=$s1{$s}{seq};\n	$s{$i}{len}=length( $s{$i\
}{seq});\n	$s{n}++;\n      }\n    return %s;\n  }\\
nsub file_contains\n  {\n    my ($file, $tag, $max\
)=(@_);\n    my ($n);\n    $n=0;\n\n    if ( !-e $\
file && ($file =~/$tag/)) {return 1;}\n    elsif (\
 !-e $file){return 0;}\n    else\n      {\n	open (\
FC, \"$file\");\n	while ( <FC>)\n	  {\n	    if ( (\
$_=~/$tag/))\n	      {\n		close (FC);\n		return 1;\
\n	      }\n	    elsif ($max && $n>$max)\n	      {\
\n		close (FC);\n		return 0;\n	      }\n	    $n++;\
\n	  }\n      }\n    close (FC);\n    return 0;\n \
 }\n\n\nsub file2string\n  {\n    my $f=@_[0];\n  \
  my $string, $l;\n    open (F,\"$f\");\n    while\
 (<F>)\n      {\n\n	$l=$_;\n	#chomp ($l);\n	$strin\
g.=$l;\n      }\n    close (F);\n    $string=~s/\\\
r\\n//g;\n    $string=~s/\\n//g;\n    return $stri\
ng;\n  }\n\n\nsub my_get_opt\n  {\n    my @list=@_\
;\n    my $cl, $a, $argv, @argl;\n\n    @argl=();\\
n    $cl=shift @list;\n    for ( $a=0; $a<=$#list;\
 $a+=3)\n      {\n	$option=$list[$a];\n	$optional=\
$list[$a+1];\n	$status=$list[$a+2];\n	$argv=\"\";\\
n	if ($cl=~/$option(\\S+)/){$argv=$1;}\n	@argl=(@a\
rgl,$argv);\n\n\n	#$optional:0=>optional\n	#$optio\
nal:1=>must be set\n	#$status: 0=>no requirement\n\
	#$status: 1=>must be an existing file\n	#$status:\
 2=>must be an installed package\n\n\n	if ($option\
al==0){;}\n	elsif ( $optional==1 && $argv eq \"\")\
\n	  {\n\n	    myexit(flush_error(\"Option $option\
 must be set\"));\n\n	  }\n	if ($status==0){;}\n	e\
lsif ($status ==1 && $argv ne \"\" && !-e $argv)\n\
	  {\n	     myexit(flush_error(\"File $argv must e\
xist\"));\n\n	  }\n	elsif ( $status==2 && $argv ne\
 \"\" && &check_pg_is_installed ($argv)==0)\n	  {\\
n	    myexit(flush_error(\"$argv is not installed\\
"));\n\n	  }\n      }\n\n    return @argl;\n    }\\
n\nsub tag2value\n  {\n\n    my $tag=(@_[0]);\n   \
 my $word=(@_[1]);\n    my $return;\n\n    $tag=~/\
$word=\"([^\"]+)\"/;\n    $return=$1;\n    return \
$return;\n  }\n\nsub hit_tag2pdbid\n  {\n    my $t\
ag=(@_[0]);\n    my $pdbid;\n\n    $tag=~/id=\"(\\\
S+)\"/;\n    $pdbid=$1;\n    $pdbid=~s/_//;\n    r\
eturn $pdbid;\n  }\nsub id2pdbid\n  {\n    my $in=\
@_[0];\n    my $id;\n\n    $in=~/(\\S+)/;\n    $id\
=$in;\n    $id=~s/PDB/pdb/g;\n\n    if ($id =~/pdb\
(.*)/){$id=$1;}\n    elsif ( $id=~/(\\S+)\\s+mol:p\
rotein/){$id=$1;}\n    $id=~s/[:|��_]//g;\n   \
 return $id;\n  }\nsub set_blast_type\n  {\n    my\
 $file =@_[0];\n    if (&file_contains ($file,\"EB\
IApplicationResult\",100)){$BLAST_TYPE=\"EBI\";}\n\
    elsif (&file_contains ($file,\"NCBI_BlastOutpu\
t\",100)) {$BLAST_TYPE=\"NCBI\";}\n    else\n     \
 {\n	$BLAST_TYPE=\"\";\n      }\n    return $BLAST\
_TYPE;\n  }\nsub is_valid_blast_xml\n    {\n      \
my $file=shift;\n      my $line;\n\n\n      if ( !\
-e $file) {return 0;}\n      $line=&file2tail ($fi\
le,100);\n\n      if ( $line=~/<\\/EBIApplicationR\
esult/ || $line=~/<\\/NCBI_BlastOutput/ || $line=~\
/<\\/BlastOutput/ ){return 1;}\n      return 0;\n \
   }\nsub file2blast_flavor\n      {\n	my $file=sh\
ift;\n	if (&file_contains ($file,\"EBIApplicationR\
esult\",100)){return \"EBI\";}\n	elsif (&file_cont\
ains ($file,\"NCBI_BlastOutput\",100)){return \"NC\
BI\";}\n	else {return \"UNKNOWN\";}\n      }\nsub \
blast_xml2profile\n  {\n    my ($name,$seq,$maxid,\
 $minid, $mincov, $file)=(@_);\n    my (%p, $a, $s\
tring, $n);\n\n\n\n    if ($BLAST_TYPE eq \"EBI\" \
|| &file_contains ($file,\"EBIApplicationResult\",\
100)){%p=ebi_blast_xml2profile(@_);}\n    elsif ($\
BLAST_TYPE eq \"NCBI\" || &file_contains ($file,\"\
NCBI_BlastOutput\",100)){%p=ncbi_blast_xml2profile\
(@_);}\n    else\n      {\n	myexit(add_error ( $$,\
$$,getppid(), \"BLAST_FAILURE::unkown XML\",$CL));\
\n      }\n    for ($a=0; $a<$p{n}; $a++)\n      {\
\n	my $name=$p{$a}{name};\n	$p{$name}{seq}=$p{$a}{\
seq};\n	$p{$name}{index}=$a;\n      }\n    return \
%p;\n  }\nsub ncbi_tblastx_xml2lib_file\n  {\n    \
my  ($outlib,$string)=(@_);\n    my ($L,$l, $a,$b,\
$c,$d,$i,$nhits,@identifyerL);\n    my (%ITERATION\
);\n\n    open (F, \">>$outlib\");\n\n    $seq=~s/\
[^a-zA-Z]//g;\n    $L=length ($seq);\n\n    %ITERA\
TION=xml2tag_list ($string, \"Iteration\");\n    f\
or ($i=0; $i<$ITERATION{n};$i++)\n      {\n	my ($q\
index, $qlen, %hit, $string);\n	$string=$ITERATION\
{$i}{body};\n\n	$qindex=xmltag2value($string,\"Ite\
ration_iter-num\");\n	$qlen  =xmltag2value($string\
,\"Iteration_query-len\");\n	%hit=&xml2tag_list  (\
$string, \"Hit\");\n\n	for ($a=0; $a<$hit{n}; $a++\
)\n	  {\n	    my ($string);\n	    $string=$hit{$a}\
{body};\n\n	    $hindex=xmltag2value($string,\"Hit\
_accession\")+1;\n	    if ($hindex<=$qindex){next;\
}\n	    else  {print F  \"# $qindex $hindex\\n\";}\
\n\n\n	    $hlen=xmltag2value  ($string,\"Hit_len\\
");\n	    %HSP=&xml2tag_list  ($string, \"Hsp\");\\
n\n	    for ($b=0; $b<$HSP{n}; $b++)\n	      {\n		\
my ($string, $qs,$qe,$qf,$hs,$he,$hf,$s, $d, $e);\\
n		$string=$HSP{$b}{body};\n\n		$qs=xmltag2value  \
($string,\"Hsp_query-from\");\n		$qe=xmltag2value \
 ($string,\"Hsp_query-to\");\n		$qf=xmltag2value  \
($string,\"Hsp_query-frame\");\n\n		$hs=xmltag2val\
ue  ($string,\"Hsp_hit-from\");\n		$he=xmltag2valu\
e  ($string,\"Hsp_hit-to\");\n		$hf=xmltag2value  \
($string,\"Hsp_hit-frame\");\n\n		$s=xmltag2value \
 ($string,\"Hsp_identity\");\n		$l=xmltag2value  (\
$string,\"Hsp_align-len\");\n		$s=int(($s*100)/$l)\
;\n\n		if ($qf>0)\n		  {$rqs=$qs; $rqe=$qe;}\n		el\
se\n		  {\n		    $rqe=($qlen-$qs)+1;\n		    $rqs=(\
$qlen-$qe)+1;\n		  }\n\n		if ($hf>0)\n		  {$rhs=$h\
s; $rhe=$he;}\n		else\n		  {\n		    $rhe=($hlen-$h\
s)+1;\n		    $rhs=($hlen-$he)+1;\n		  }\n		for ($d\
=0,$e=$rqs; $e<$rqe; $e++,$d++)\n		  {\n		    my (\
$r1,$r2);\n		    $r1=$e;\n		    $r2=$rhs+$d;\n		  \
  print F \" $r1 $r2 $s 0\\n\";\n		  }\n	      }\n\
	  }\n      }\n    print F \"! SEQ_1_TO_N\\n\";\n\\
n    close (F);\n    return %lib;\n  }\n\nsub ncbi\
_tblastpx_xml2lib_file\n  {\n    my  ($outlib,$str\
ing,%s)=(@_);\n    my ($L,$l, $a,$b,$c,$d,$i,$nhit\
s,@identifyerL);\n    my (%ITERATION,%hdes, %qdes)\
;\n\n    open (F, \">>$outlib\");\n\n    $seq=~s/[\
^a-zA-Z]//g;\n    $L=length ($seq);\n\n    %ITERAT\
ION=xml2tag_list ($string, \"Iteration\");\n    fo\
r ($i=0; $i<$ITERATION{n};$i++)\n      {\n	my ($qi\
ndex, $qlen, %hit, $string);\n	$string=$ITERATION{\
$i}{body};\n\n	$qdef=xmltag2value($string,\"Iterat\
ion_query-def\");\n	%qdes=&tblastpx_name2descripti\
on($qdef,%s);\n	$qlen  =xmltag2value($string,\"Ite\
ration_query-len\");\n	%hit=&xml2tag_list  ($strin\
g, \"Hit\");\n\n	for ($a=0; $a<$hit{n}; $a++)\n	  \
{\n	    my ($string);\n	    $string=$hit{$a}{body}\
;\n	    $hdef=xmltag2value($string,\"Hit_def\");\n\
	    %hdes=&tblastpx_name2description($hdef,%s);\n\
	    if ($hdes{index}<=$qdes{index}){next;}\n	    \
else  {print F  \"# $qdes{index} $hdes{index}\\n\"\
;}\n\n\n	    $hlen=xmltag2value  ($string,\"Hit_le\
n\");\n	    %HSP=&xml2tag_list  ($string, \"Hsp\")\
;\n\n	    for ($b=0; $b<$HSP{n}; $b++)\n	      {\n\
		my ($string, $l,$qs,$qe,$qf,$hs,$he,$hf,$s, $d, \
$e, @s1, @s2);\n		$string=$HSP{$b}{body};\n\n		$qs\
=xmltag2value  ($string,\"Hsp_query-from\");\n		$q\
e=xmltag2value  ($string,\"Hsp_query-to\");\n		$qf\
=$qdes{frame};\n		$qseq=xmltag2value  ($string,\"H\
sp_qseq\");\n\n		$hs=xmltag2value  ($string,\"Hsp_\
hit-from\");\n		$he=xmltag2value  ($string,\"Hsp_h\
it-to\");\n		$hf=$hdes{frame};\n		$hseq=xmltag2val\
ue  ($string,\"Hsp_hseq\");\n\n		$s=xmltag2value  \
($string,\"Hsp_identity\");\n		$l=xmltag2value  ($\
string,\"Hsp_align-len\");\n		$s=int(($s*100)/$l);\
\n		@s1=tblastpx_hsp2coordinates($qseq,$qs,$qe,%qd\
es);\n		@s2=tblastpx_hsp2coordinates($hseq,$hs,$he\
,%hdes);\n\n\n		for ($f=0; $f<=$#s1; $f++)\n		  {\\
n		    if ($s1[$f]==-1 || $s2[$f]==-1){next;}\n		 \
   else\n		      {\n			print F \" $s1[$f] $s2[$f] \
$s 0\\n\";\n		      }\n		  }\n	      }\n	  }\n    \
  }\n    print F \"! SEQ_1_TO_N\\n\";\n\n    close\
 (F);\n    return %lib;\n  }\nsub tblastpx_hsp2coo\
rdinates\n  {\n    my ($seq, $s, $e, %des)=@_;\n  \
  my @list;\n    my @sa;\n    my @gap=(-1,-1,-1);\\
n\n    $s=$des{start}+3*($s-1);\n\n    if ($des{st\
rand} eq \"d\"){;}\n    else {$s=($des{length}-$s)\
+1;}\n\n    foreach $c (split (//,$seq))\n      {\\
n	if ( $c eq '-'){push (@list,@gap);}\n	elsif ($de\
s{strand} eq \"d\")\n	  {\n	    push(@list,$s++,$s\
++,$s++);\n	  }\n	else\n	  {\n	    push(@list, $s-\
-,$s--,$s--);\n	  }\n      }\n    return @list;\n \
 }\n\nsub tblastpx_name2description\n  {\n    my (\
$name, %s)=@_;\n    my @at=split(\"__\", $name);\n\
    my %des;\n\n    $des{name}=$at[0];\n    $des{s\
trand}=$at[1];\n\n    $des{start}=$at[2];\n    $de\
s{end}=$at[3];\n    $des{length}=$at[4];\n    $des\
{index}=$s{$at[0]}{order}+1;\n    return %des;\n  \
}\nsub ncbi_blast_xml2profile\n  {\n    my ($name,\
$seq,$maxid, $minid, $mincov, $string)=(@_);\n    \
my ($L,$l, $a,$b,$c,$d,$nhits,@identifyerL);\n\n\n\
    $seq=~s/[^a-zA-Z]//g;\n    $L=length ($seq);\n\
\n    #This is causing the NCBI parser to fail whe\
n Iteration_query-def is missing\n    #%query=&xml\
2tag_list ($string, \"Iteration_query-def\");\n   \
 #$name=$query{0}{body};\n\n    %hit=&xml2tag_list\
 ($string, \"Hit\");\n\n\n    for ($nhits=0,$a=0; \
$a<$hit{n}; $a++)\n      {\n	my ($ldb,$id, $identi\
ty, $expectation, $start, $end, $coverage, $r);\n	\
my (%ID,%DE,%HSP);\n\n	$ldb=\"\";\n\n	%ID=&xml2tag\
_list ($hit{$a}{body}, \"Hit_id\");\n	$identifyer=\
$ID{0}{body};\n\n	%DE=&xml2tag_list ($hit{$a}{body\
}, \"Hit_def\");\n	$definition=$DE{0}{body};\n\n	%\
HSP=&xml2tag_list ($hit{$a}{body}, \"Hsp\");\n	for\
 ($b=0; $b<$HSP{n}; $b++)\n	  {\n	    my (%START,%\
END,%E,%I,%Q,%M);\n\n\n	    %START=&xml2tag_list (\
$HSP{$b}{body}, \"Hsp_query-from\");\n	    %HSTART\
=&xml2tag_list ($HSP{$b}{body}, \"Hsp_hit-from\");\
\n\n	    %LEN=  &xml2tag_list ($HSP{$b}{body}, \"H\
sp_align-len\");\n	    %END=  &xml2tag_list ($HSP{\
$b}{body}, \"Hsp_query-to\");\n	    %HEND=  &xml2t\
ag_list ($HSP{$b}{body}, \"Hsp_hit-to\");\n	    %E\
=&xml2tag_list     ($HSP{$b}{body}, \"Hsp_evalue\"\
);\n	    %I=&xml2tag_list     ($HSP{$b}{body}, \"H\
sp_identity\");\n	    %Q=&xml2tag_list     ($HSP{$\
b}{body}, \"Hsp_qseq\");\n	    %M=&xml2tag_list   \
  ($HSP{$b}{body}, \"Hsp_hseq\");\n\n	    for ($e=\
0; $e<$Q{n}; $e++)\n\n	      {\n		$qs=$Q{$e}{body}\
;\n		$ms=$M{$e}{body};\n\n		$expectation=$E{$e}{bo\
dy};\n		$identity=($LEN{$e}{body}==0)?0:$I{$e}{bod\
y}/$LEN{$e}{body}*100;\n		$start=$START{$e}{body};\
\n		$end=$END{$e}{body};\n		$Hstart=$HSTART{$e}{bo\
dy};\n		$Hend=$HEND{$e}{body};\n\n		$coverage=($L)\
?(($end-$start)*100)/$L:0;\n\n		if ($identity>$max\
id || $identity<$minid || $coverage<$mincov){next;\
}\n		@lr1=(split (//,$qs));\n		@lr2=(split (//,$ms\
));\n		$l=$#lr1+1;\n		for ($c=0;$c<$L;$c++){$p[$nh\
its][$c]=\"-\";}\n		for ($d=0,$c=0; $c<$l; $c++)\n\
		  {\n		    $r=$lr1[$c];\n		    if ( $r=~/[A-Za-z\
]/)\n		      {\n\n			$p[$nhits][$d + $start-1]=$lr\
2[$c];\n			$d++;\n		      }\n		  }\n		$Qseq[$nhits\
]=$qs;\n		$Hseq[$nhits]=$ms;\n		$QstartL[$nhits]=$\
start;\n		$HstartL[$nhits]=$Hstart;\n		$identityL[\
$nhits]=$identity;\n		$endL[$nhits]=$end;\n		$defi\
nitionL[$nhits]=$definition;\n		$identifyerL[$nhit\
s]=$identifyer;\n		$comment[$nhits]=\"$ldb|$identi\
fyer [Eval=$expectation][id=$identity%][start=$Hst\
art end=$Hend]\";\n		$nhits++;\n	      }\n	  }\n  \
    }\n\n\n    $profile{n}=0;\n    $profile{$profi\
le{n}}{name}=$name;\n    $profile{$profile{n}}{seq\
}=$seq;\n    $profile {n}++;\n\n    for ($a=0; $a<\
$nhits; $a++)\n      {\n	$n=$a+1;\n\n	$profile{$n}\
{name}=\"$name\\_$a\";\n	$profile{$n}{seq}=\"\";\n\
	$profile{$n}{Qseq}=$Qseq[$a];\n	$profile{$n}{Hseq\
}=$Hseq[$a];\n	$profile{$n}{Qstart}=$QstartL[$a];\\
n	$profile{$n}{Hstart}=$HstartL[$a];\n	$profile{$n\
}{identity}=$identityL[$a];\n	$profile{$n}{definit\
ion}=$definitionL[$a];\n	$profile{$n}{identifyer}=\
$identifyerL[$a];\n	$profile{$n}{comment}=$comment\
[$a];\n\n	for ($b=0; $b<$L; $b++)\n	  {\n	    if (\
$p[$a][$b])\n	      {\n		$profile{$n}{seq}.=$p[$a]\
[$b];\n	      }\n	    else\n	      {\n		$profile{$\
n}{seq}.=\"-\";\n	      }\n	  }\n      }\n\n    $p\
rofile{n}=$nhits+1;\n    return %profile;\n  }\nsu\
b ebi_blast_xml2profile\n  {\n    my ($name,$seq,$\
maxid, $minid, $mincov, $string)=(@_);\n    my ($L\
,$l, $a,$b,$c,$d,$nhits,@identifyerL,$identifyer);\
\n\n\n\n    $seq=~s/[^a-zA-Z]//g;\n    $L=length (\
$seq);\n    %hit=&xml2tag_list ($string, \"hit\");\
\n\n    for ($nhits=0,$a=0; $a<$hit{n}; $a++)\n   \
   {\n	my ($ldb,$id, $identity, $expectation, $sta\
rt, $end, $coverage, $r);\n	my (%Q,%M,%E,%I);\n\n	\
$ldb=&tag2value ($hit{$a}{open}, \"database\");\n	\
$identifyer=&tag2value ($hit{$a}{open}, \"id\");\n\
\n	$description=&tag2value ($hit{$a}{open}, \"desc\
ription\");\n\n	%Q=&xml2tag_list ($hit{$a}{body}, \
\"querySeq\");\n	%M=&xml2tag_list ($hit{$a}{body},\
 \"matchSeq\");\n	%E=&xml2tag_list ($hit{$a}{body}\
, \"expectation\");\n	%I=&xml2tag_list ($hit{$a}{b\
ody}, \"identity\");\n\n\n	for ($b=0; $b<$Q{n}; $b\
++)\n	  {\n\n	    $qs=$Q{$b}{body};\n	    $ms=$M{$\
b}{body};\n\n	    $expectation=$E{$b}{body};\n	   \
 $identity=$I{$b}{body};\n\n\n	    $start=&tag2val\
ue ($Q{$b}{open}, \"start\");\n	    $end=&tag2valu\
e ($Q{$b}{open}, \"end\");\n	    $startM=&tag2valu\
e ($M{$b}{open}, \"start\");\n	    $endM=&tag2valu\
e ($M{$b}{open}, \"end\");\n	    $coverage=(($end-\
$start)*100)/$L;\n\n	   # print \"$id: ID: $identi\
ty COV: $coverage [$start $end]\\n\";\n\n	    if (\
$identity>$maxid || $identity<$minid || $coverage<\
$mincov){next;}\n	    # print \"KEEP\\n\";\n\n\n	 \
   @lr1=(split (//,$qs));\n	    @lr2=(split (//,$m\
s));\n	    $l=$#lr1+1;\n	    for ($c=0;$c<$L;$c++)\
{$p[$nhits][$c]=\"-\";}\n	    for ($d=0,$c=0; $c<$\
l; $c++)\n	      {\n		$r=$lr1[$c];\n		if ( $r=~/[A\
-Za-z]/)\n		  {\n\n		    $p[$nhits][$d + $start-1]\
=$lr2[$c];\n		    $d++;\n		  }\n	      }\n\n	    $\
Qseq[$nhits]=$qs;\n	    $Hseq[$nhits]=$ms;\n	    $\
QstartL[$nhits]=$start;\n	    $HstartL[$nhits]=$Hs\
tart;\n	    $identityL[$nhits]=$identity;\n	    $e\
ndL[$nhits]=$end;\n	    $definitionL[$nhits]=$defi\
nition;\n	    $identifyerL[$nhits]=$identifyer;\n	\
    $comment[$nhits]=\"$ldb|$identifyer [Eval=$exp\
ectation][id=$identity%][start=$startM end=$endM]\\
";\n	    $nhits++;\n	  }\n      }\n\n    $profile{\
n}=0;\n    $profile{$profile{n}}{name}=$name;\n   \
 $profile{$profile{n}}{seq}=$seq;\n    $profile {n\
}++;\n\n    for ($a=0; $a<$nhits; $a++)\n      {\n\
	$n=$a+1;\n	$profile{$n}{name}=\"$name\\_$a\";\n	$\
profile{$n}{seq}=\"\";\n	$profile{$n}{Qseq}=$Qseq[\
$a];\n	$profile{$n}{Hseq}=$Hseq[$a];\n	$profile{$n\
}{Qstart}=$QstartL[$a];\n	$profile{$n}{Hstart}=$Hs\
tartL[$a];\n	$profile{$n}{identity}=$identityL[$a]\
;\n	$profile{$n}{definition}=$definitionL[$a];\n	$\
profile{$n}{identifyer}=$identifyerL[$a];\n	$profi\
le{$n}{comment}=$comment[$a];\n\n	for ($b=0; $b<$L\
; $b++)\n	  {\n	    if ($p[$a][$b])\n	      {\n		$\
profile{$n}{seq}.=$p[$a][$b];\n	      }\n	    else\
\n	      {\n		$profile{$n}{seq}.=\"-\";\n	      }\\
n	  }\n      }\n    $profile{n}=$nhits+1;\n\n    r\
eturn %profile;\n  }\nsub output_profile\n  {\n   \
 my ($outfile,$profileR, $trim)=(@_);\n    my ($a)\
;\n    my %profile=%$profileR;\n    my $P= new Fil\
eHandle;\n    my $tmp=vtmpnam();\n\n    open ($P, \
\">$tmp\");\n    for ($a=0; $a<$profile{n}; $a++)\\
n      {\n	print $P \">$profile{$a}{name} $profile\
{$a}{comment}\\n$profile{$a}{seq}\\n\";\n      }\n\
    close ($P);\n\n    if ( $trim)\n      {\n	&saf\
e_system (\"t_coffee -other_pg seq_reformat -in $t\
mp -action +trim _aln_%%$trim\\_K1 -output fasta_a\
ln -out $outfile\");\n      }\n    else\n      {\n\
	&safe_system (\"mv $tmp $outfile\");\n      }\n  \
  return;\n  }\nsub blast_xml2hit_list\n  {\n    m\
y $string=(@_[0]);\n    return &xml2tag_list ($str\
ing, \"hit\");\n  }\nsub xmltag2value\n  {\n    my\
 ($string_in, $tag)=@_;\n    my %TAG;\n    %TAG=xm\
l2tag_list ($string_in, $tag);\n    return $TAG{0}\
{body};\n  }\n\nsub xml2tag_list\n  {\n    my ($st\
ring_in,$tag)=@_;\n    my $tag_in, $tag_out;\n    \
my %tag;\n\n    if (-e $string_in)\n      {\n	$str\
ing=&file2string ($string_in);\n      }\n    else\\
n      {\n	$string=$string_in;\n      }\n    $tag_\
in1=\"<$tag \";\n    $tag_in2=\"<$tag>\";\n    $ta\
g_out=\"/$tag>\";\n    $string=~s/>/>##1/g;\n    $\
string=~s/</##2</g;\n    $string=~s/##1/<#/g;\n   \
 $string=~s/##2/#>/g;\n    @l=($string=~/(\\<[^>]+\
\\>)/g);\n    $tag{n}=0;\n    $in=0;$n=-1;\n\n\n\n\
    foreach $t (@l)\n      {\n\n	$t=~s/<#//;\n	$t=\
~s/#>//;\n\n	if ( $t=~/$tag_in1/ || $t=~/$tag_in2/\
)\n	  {\n\n	    $in=1;\n	    $tag{$tag{n}}{open}=$\
t;\n	    $n++;\n\n	  }\n	elsif ($t=~/$tag_out/)\n	\
  {\n\n\n	    $tag{$tag{n}}{close}=$t;\n	    $tag{\
n}++;\n	    $in=0;\n	  }\n	elsif ($in)\n	  {\n\n	 \
   $tag{$tag{n}}{body}.=$t;\n	  }\n      }\n\n    \
return %tag;\n  }\n\n\nsub seq2gor_prediction\n  {\
\n    my ($name, $seq,$infile, $outfile, $gor_seq,\
 $gor_obs)=(@_);\n    my ($l);\n\n    `gorIV -prd \
$infile -seq $gor_seq -obs $gor_obs > gor_tmp`;\n \
   open (GR, \">$outfile\");\n    open (OG, \"gor_\
tmp\");\n\n    while (<OG>)\n      {\n\n	$l=$_;\n	\
if ($l=~/\\>/){print GR \"$l\";}\n	elsif ( $l=~/Pr\
edicted Sec. Struct./)\n	  {\n	    $l=~s/Predicted\
 Sec. Struct\\.//;\n	    print GR \"$l\";\n	  }\n \
     }\n    close (GR);\n    close (OG);\n    retu\
rn;\n  }\nsub seq2msa_tm_prediction\n  {\n    my (\
$name, $seq, $db, $infile, $outfile, $arch, $psv)=\
(@_);\n    my (%p,%gseq,%R, $blast_output, %s, $l)\
;\n    my $R2=new FileHandle;\n    my $db=\"unipro\
t\";\n    my $method=\"psitm\";\n    my $SERVER=\"\
EBI\";\n\n    $blast_output=&run_blast ($name,\"bl\
astp\", $db, $infile, \"outfile\");\n\n    if (&ca\
che_file(\"GET\",$infile,$name,$method,$db,$outfil\
e,$SERVER))\n      {\n	print \"\\tPSITM: USE Cache\
\\n\";\n	return $outfile;\n      }\n    else\n    \
  {\n	$CACHE_STATUS=\"COMPUTE CACHE\";\n	%p=blast_\
xml2profile($name,$seq,$maxid, $minid,$mincov,$bla\
st_output);\n\n\n	open (F, \">tm_input\");\n	for (\
my $a=0; $a<$p{n}; $a++)\n	  {\n	    my $s;\n\n	  \
  $s=$p{$a}{seq};\n	    $s=uc($s);\n	    print F \\
">$p{$a}{name}\\n$s\\n\";\n	    #print stdout \">$\
p{$a}{name}\\n$s\\n\";\n	  }\n	close (F);\n	print \
\"\\tPSITM: kept  $p{n} Homologues for Sequence $p\
{0}{name}\\n\";\n	&safe_system (\"t_coffee -other_\
pg fasta_seq2hmmtop_fasta.pl -in=tm_input -out=$ou\
tfile -output=cons -cov=70 -trim=95 -arch=$arch -p\
sv=$psv\");\n	unlink (\"tm_input\");\n	&cache_file\
(\"SET\",$infile,$name,$method,$db,$outfile,$SERVE\
R);\n	return;\n      }\n  }\n\n\nsub seq2msa_gor_p\
rediction\n  {\n    my ($name, $seq,$infile, $outf\
ile, $gor_seq, $gor_obs)=(@_);\n    my (%p,%gseq,%\
R, $blast_output, %s, $l);\n    my $R2=new FileHan\
dle;\n    my $db=\"uniprot\";\n    my $method=\"ps\
igor\";\n    my $SERVER=\"EBI\";\n\n    $blast_out\
put=&run_blast ($name,\"blastp\", \"uniprot\", $in\
file, \"outfile\");\n\n    if (&cache_file(\"GET\"\
,$infile,$name,$method,$db,$outfile,$SERVER))\n   \
   {\n	print \"\\tPSIGOR: USE Cache\\n\";\n	return\
 $outfile;\n      }\n    else\n      {\n	$CACHE_ST\
ATUS=\"COMPUTE CACHE\";\n	%p=blast_xml2profile($na\
me,$seq,$maxid, $minid,$mincov,$blast_output);\n\n\
\n	open (F, \">gor_input\");\n	for (my $a=0; $a<$p\
{n}; $a++)\n	  {\n	    my $s;\n\n	    $s=$p{$a}{se\
q};\n	    $s=uc($s);\n	    print F \">$p{$a}{name}\
\\n$s\\n\";\n	    #print stdout \">$p{$a}{name}\\n\
$s\\n\";\n	  }\n	close (F);\n	print \"\\tGORTM: ke\
pt  $p{n} Homologues for Sequence $p{0}{name}\\n\"\
;\n	&safe_system (\"t_coffee -other_pg fasta_seq2h\
mmtop_fasta.pl -in=gor_input -out=$outfile -output\
=cons -cov=70 -trim=95 -gor_seq=$gor_seq -gor_obs=\
$gor_obs -mode=gor\");\n	unlink (\"tm_input\");\n	\
&cache_file(\"SET\",$infile,$name,$method,$db,$out\
file,$SERVER);\n	return;\n      }\n  }\n\n\n\nsub \
run_blast\n  {\n    my ($name, $method, $db, $infi\
le, $outfile, $run)=(@_);\n    if (!$run){$run=1;}\
\n    my $error_log=vtmpnam();\n\n    if (&cache_f\
ile(\"GET\",$infile,$name,$method,$db,$outfile,$SE\
RVER) && is_valid_blast_xml ($outfile))\n      {re\
turn $outfile;}\n    else\n      {\n	$CACHE_STATUS\
=\"COMPUTE CACHE\";\n	if ( $SERVER eq \"EBI_SOAP\"\
)\n	  {\n	    &check_configuration (\"EMAIL\",\"SO\
AP::Light\",\"INTERNET\");\n\n	    $cl_method=$met\
hod;\n	    if ($cl_method =~/wu/)\n	      {\n		$cl\
_method=~s/wu//;\n		if ( $cl_method eq \"psiblast\\
")\n		  {\n		    add_warning($$,$$,\"PSI BLAST can\
not be used with the wuBLAST Client. Use server=EB\
I Or server=LOCAL. blastp will be used instead\");\
\n		    $cl_method=\"blastp\";\n		  }\n\n		$comman\
d=\"t_coffee -other_pg wublast.pl --email $EMAIL $\
infile -D $db -p $cl_method --outfile $outfile -o \
xml>/dev/null 2>$error_log\";\n		&safe_system ( $c\
ommand);\n		if (-e \"$outfile.xml\") {`mv $outfile\
.xml $outfile`;}\n	      }\n	    else\n	      {\n	\
	if ($cl_method eq \"psiblast\"){$cl_method =\"bla\
stp -j5\";}\n\n		$command=\"t_coffee -other_pg bla\
stpgp.pl --email $EMAIL $infile -d $db --outfile $\
outfile -p $cl_method --mode PSI-Blast>/dev/null 2\
>$error_log\";\n		&safe_system ( $command);\n\n		i\
f (-e \"$outfile.xml\") {`mv $outfile.xml $outfile\
`;}\n	      }\n	  }\n	elsif ($SERVER eq \"EBI_REST\
\" || $SERVER eq \"EBI\")\n	  {\n	    $cl_method=$\
method;\n	    &check_configuration(\"EMAIL\",\"XML\
::Simple\", \"INTERNET\");\n	    if ($db eq \"unip\
rot\"){$db1=\"uniprotkb\";}\n	    else {$db1=$db;}\
\n\n	   \n	    if ($cl_method =~/wu/)\n	      {\n	\
	$cl_method=~s/wu//;\n		if ( $cl_method eq \"psibl\
ast\"){$cl_method=\"blastp\";}\n\n		$command=\"t_c\
offee -other_pg wublast_lwp.pl --email $EMAIL -D $\
db1 -p $cl_method --outfile $outfile --align 5 --s\
type protein $infile>/dev/null 2>error_log\";\n	  \
    }\n	    else\n	      {\n		if ( $cl_method =~/p\
siblast/){$cl_method =\"blastp -j5\";}\n		$command\
=\"t_coffee -other_pg ncbiblast_lwp.pl --email $EM\
AIL -D $db1 -p $cl_method --outfile $outfile --ali\
gn 5 --stype protein $infile>/dev/null 2>$error_lo\
g\";\n	      }\n	    &safe_system ( $command,5);\n\
	    if (-e \"$outfile.out.xml\") {`mv $outfile.ou\
t.xml $outfile`;}\n	    elsif (-e \"$outfile.xml.x\
ml\"){`mv $outfile.xml.xml $outfile`;}\n	    elsif\
 (-e \"$outfile.out..xml\") {`mv $outfile.out..xml\
 $outfile`;}\n	    elsif (-e \"$outfile.xml..xml\"\
){`mv $outfile.xml..xml $outfile`;}\n	  }\n	elsif \
($SERVER eq \"NCBI\")\n	  {\n	    &check_configura\
tion (\"INTERNET\");\n	    if ($db eq \"uniprot\")\
{$cl_db=\"swissprot\";}\n	    else {$cl_db=$db;}\n\
\n	    if ( $method eq \"psiblast\")\n	      {\n		\
add_warning($$,$$,\"PSI BLAST cannot be used with \
the NCBI BLAST Client. Use server=EBI Or server=LO\
CAL. blastp will be used instead\");\n		$cl_method\
=\"blastp\";\n	      }\n	    else\n	      {\n		$cl\
_method=$method;\n	      }\n	      \n	    &check_c\
onfiguration ($cl_method);  \n	    $command=\"$cl_\
method -db $cl_db -query $infile -out $outfile -ou\
tfmt 5 -remote\";\n	    &safe_system ($command);\n\
	  }\n	elsif ($SERVER =~/CLIENT_(.*)/)\n	  {\n	   \
 my $client=$1;\n	    $command=\"$client -p $metho\
d -d $db -i $infile -o $outfile -m 7\";\n	    &saf\
e_system ($command);\n	  }\n	elsif ( $SERVER eq \"\
LOCAL_blastall\")\n	  {\n	    &check_configuration\
 (\"blastall\");\n	    if ($method eq \"blastp\")\\
n	      {\n		$command=\"blastall -d $db -i $infile\
 -o $outfile -m7 -p blastp\";\n	      }\n	    &saf\
e_system ($command);\n	  }\n	elsif ( $SERVER eq \"\
LOCAL\")\n	  {\n\n	    if ($ENV{\"BLAST_DB_DIR\"})\
\n	      {\n		$x=$ENV{\"BLAST_DB_DIR\"};\n		$cl_db\
=\"$x$db\";\n	      }\n	    else\n	      {\n		$cl_\
db=$db;\n	      }\n\n        ##\n		## BLAST+ provi\
de different binaries names and CLI options\n		## \
Use the 'legacy_blast.pl' to keep compatibility wi\
th old blast commands\n		##\n		$path=`which legacy\
_blast.pl 2>/dev/null`;  \n		$path=`dirname $path`\
; \n		chomp($path);\n	    if ($method eq \"blastp\\
")\n	      {\n		&check_configuration(\"legacy_blas\
t.pl\");\n		$command=\"legacy_blast.pl blastpgp --\
path $path -d $cl_db -i $infile -o $outfile -m7 -j\
1\";\n	      }\n	    elsif ($method eq \"psiblast\\
")\n	      {\n		&check_configuration(\"legacy_blas\
t.pl\");\n		$command=\"legacy_blast.pl blastpgp --\
path $path -d $cl_db -i $infile -o $outfile -m7 -j\
5\";\n	      }\n	    elsif ($method eq \"blastn\")\
\n	      {\n		&check_configuration(\"legacy_blast.\
pl\");\n		$command=\"legacy_blast.pl blastall --pa\
th $path -p blastn -d $cl_db -i $infile -o $outfil\
e -m7 -W6\";\n	      }\n	    &safe_system ($comman\
d);\n	  }\n	else\n	  {\n\n	    myexit(add_error (E\
XIT_FAILURE,$$,$$,getppid(), \"BLAST_FAILURE::Unkn\
ownServer\",$CL));\n	  }\n\n\n	#Check that everyth\
ing went well\n\n	if ( !-e $outfile || !&is_valid_\
blast_xml($outfile))\n	  {\n\n	    if ( -e $outfil\
e)\n	      {\n		add_warning ($$,$$,\"Corrupted Bla\
st Output (Run $run)\");\n		unlink($outfile);\n	  \
    }\n	    if ( -e $error_log)\n	      {\n\n		my \
$error_msg=file2string ($error_log);\n\n		if ( $er\
ror_msg =~/enter a valid email/)\n		  {\n		    mye\
xit(add_error (EXIT_FAILURE,$$,$$,getppid(), \"BLA\
ST_FAILURE::Invalid_or_rejected_email::$EMAIL\", \\
"$command\"));\n		  }\n	      }\n	    if ( $run==$\
BLAST_MAX_NRUNS)\n	      {\n\n		myexit(add_error (\
EXIT_FAILURE,$$,$$,getppid(), \"BLAST_FAILURE::Unk\
nownReason\", \"$command\"));\n	      }\n	    else\
\n	      {\n		my $out;\n		if ($SERVER eq \"NCBI\")\
 {$SERVER=\"EBI\"; }\n		elsif ($SERVER eq \"EBI\")\
{$SERVER=\"NCBI\";}\n		add_warning ($$,$$,\"Blast \
for $name failed (Run: $run out of $BLAST_MAX_NRUN\
S. Use $SERVER)\");\n		$out=&run_blast ($name, $me\
thod, $db,$infile, $outfile, $run+1);\n		if ($SERV\
ER eq \"NCBI\") {$SERVER=\"EBI\"; }\n		elsif ($SER\
VER eq \"EBI\"){$SERVER=\"NCBI\";}\n		return $out;\
\n	      }\n	  }\n\n	&cache_file(\"SET\",$infile,$\
name,$method,$db,$outfile,$SERVER);\n	#system (\"c\
p $outfile ~/Dropbox/tmp/cedric.out\");\n	#die;\n	\
return $outfile;\n      }\n  }\n\nsub cache_file\n\
  {\n    my ($cache_mode,$infile,$name,$method,$db\
, $outfile,$server)=(@_);\n    my $cache_file;\n  \
  #Protect names so that they can be turned into l\
egal filenames\n    $name=&clean_file_name ($name)\
;\n\n    if ($db=~/\\//)\n      {\n	$db=~/([^\\/]+\
)$/;\n	$db=$1;\n      }\n    $cache_file_sh=\"$nam\
e.$method.$db.$server.tmp\";\n    $cache_file=\"$C\
ACHE/$name.$method.$db.$server.tmp\";\n\n    if ($\
infile ne \"\")\n      {\n	$cache_file_infile_sh=\\
"$name.$method.$db.$server.infile.tmp\";\n	$cache_\
file_infile=\"$CACHE/$name.$method.$db.$server.inf\
ile.tmp\";\n      }\n\n    if ($cache_mode eq \"GE\
T\")\n      {\n	if ($CACHE eq \"\" || $CACHE eq \"\
no\" || $CACHE eq \"ignore\"  || $CACHE eq \"local\
\" || $CACHE eq \"update\"){return 0;}\n	elsif ( !\
-d $CACHE)\n	  {\n	    print STDERR \"ERROR: Cache\
 Dir: $CACHE Does not Exist\";\n	    return 0;\n	 \
 }\n	else\n	  {\n	    if ( -e $cache_file && &fast\
a_file1_eq_fasta_file2($infile,$cache_file_infile)\
==1)\n	      {\n		`cp $cache_file $outfile`;\n		$C\
ACHE_STATUS=\"READ CACHE\";\n		return 1;\n	      }\
\n	  }\n      }\n    elsif ($cache_mode eq \"SET\"\
)\n      {\n	if ($CACHE eq \"\" || $CACHE eq \"no\\
" || $CACHE eq \"ignore\"  || $CACHE eq \"local\" \
|| $CACHE eq \"update\"){return 0;}\n	elsif ( !-d \
$CACHE)\n	  {\n	    print STDERR \"ERROR: Cache Di\
r: $CACHE Does not Exist\";\n	    return 0;\n	  }\\
n	elsif (-e $outfile)\n	  {\n	    `cp $outfile $ca\
che_file`;\n	    if ($cache_file_infile ne \"\"){ \
`cp $infile $cache_file_infile`;}\n\n	    #functio\
ns for updating the cache\n	    #`t_coffee -other_\
pg clean_cache.pl -file $cache_file_sh -dir $CACHE\
`;\n	    #`t_coffee -other_pg clean_cache.pl -file\
 $cache_file_infile_sh -dir $CACHE`;\n	    return \
1;\n	  }\n      }\n    $CACHE_STATUS=\"COMPUTE CAC\
HE\";\n    return 0;\n  }\nsub file1_eq_file2\n  {\
\n    my ($f1, $f2)=@_;\n    if ( $f1 eq \"\"){ret\
urn 1;}\n    elsif ( $f2 eq \"\"){return 1;}\n    \
elsif ( !-e $f1){return 0;}\n    elsif ( !-e $f2){\
return 0;}\n    elsif ($f1 eq \"\" || $f2 eq \"\" \
|| `diff $f1 $f2` eq \"\"){return 1;}\n\n    retur\
n 0;\n  }\nsub clean_file_name\n  {\n    my $name=\
@_[0];\n\n    $name=~s/[^A-Za-z1-9.-]/_/g;\n    re\
turn $name;\n  }\nsub url2file\n  {\n    my ($addr\
ess, $out)=(@_);\n\n    if (&pg_is_installed (\"wg\
et\"))\n	{\n	  return &safe_system (\"wget $addres\
s -O$out >/dev/null 2>/dev/null\");\n	}\n    elsif\
 (&pg_is_installed (\"curl\"))\n      {\n	return &\
safe_system (\"curl $address -o$out >/dev/null 2>/\
dev/null\");\n      }\n    else\n      {\n	myexit(\
flus_error(\"neither curl nor wget are installed. \
Imnpossible to fectch remote file\"));\n	exit ($EX\
IT_FAILURE);\n      }\n  }\nsub fasta_file1_eq_fas\
ta_file2\n  {\n    my ($f1, $f2)=@_;\n    my (%s1,\
 %s2);\n    my @names;\n    %s1=read_fasta_seq ($f\
1);\n    %s2=read_fasta_seq ($f2);\n\n    @names=(\
keys (%s1));\n\n    foreach $n (keys(%s1))\n      \
{\n	if ($s1{$n}{seq} ne $s2{$n}{seq}){return 0;}\n\
      }\n\n    foreach $n (keys(%s2))\n      {\n	i\
f ($s1{$n}{seq} ne $s2{$n}{seq}){return 0;}\n     \
 }\n    return 1;\n  }\n\n\n\nsub read_template_fi\
le\n{\n	my $pdb_templates = @_[0];\n	open (TEMP, \\
"<$pdb_templates\");\n	my %temp_h;\n	while (<TEMP>\
)\n{\n		$line = $_;\n 		$line =~/(\\S+)\\s(\\S+)/;\
\n 		$temp_h{$1}= $2;\n}\n	close(TEMP);\n	return %\
temp_h;\n}\n\nsub calc_rna_template\n{\n	my ($mode\
, $infile, $pdbfile, $outfile)=@_;\n	my %s, %h ;\n\
	my $result;\n	my (@profiles);\n	&set_temporary_di\
r (\"set\",$infile,\"seq.pep\");\n	%s=read_fasta_s\
eq (\"seq.pep\");\n\n	%pdb_template_h = &read_temp\
late_file($pdbfile);\n	my $pdb_chain;\n	open (R, \\
">result.aln\");\n\n\n	#print stdout \"\\n\";\n	fo\
reach $seq (keys(%s))\n	{\n		if ($pdb_template_h{$\
seq} eq \"\")\n		{\n			next;\n		}\n		open (F, \">s\
eqfile\");\n		print (F \">$s{$seq}{name}\\n$s{$seq\
}{seq}\\n\");\n		close (F);\n		$pdb_chain = $pdb_t\
emplate_h{$seq};\n		$lib_name=\"$s{$seq}{name}.rfo\
ld\";\n		$lib_name=&clean_file_name ($lib_name);\n\
		safe_system (\"secondary_struc.py seqfile $CACHE\
$pdb_chain  $lib_name\");\n		\n		if ( !-e $lib_nam\
e)\n		{\n		myexit(flush_error(\"secondary_struc.py\
 failed to compute the secondary structure of PDB \
 $s{$seq}{name}\"));\n			myexit ($EXIT_FAILURE);\n\
		}\n		else\n		{\n			print stdout \"\\tProcess: >$\
s{$seq}{name} _F_ $lib_name\\n\";\n			print R \">$\
s{$seq}{name} _F_ $lib_name\\n\";\n		}\n		unshift \
(@profiles, $lib_name);\n	}\n	close (R);\n	&set_te\
mporary_dir (\"unset\",$mode, $method,\"result.aln\
\",$outfile, @profiles);\n}\n\n\n\nsub seq2rna_pai\
r{\n	my ($mode, $pdbfile1, $pdbfile2, $method, $pa\
ram, $outfile)=@_;\n\n	if ($method eq \"runsara.py\
\")\n	{\n	  open(TMP,\"<$pdbfile1\");\n	  my $coun\
t = 0;\n	  my $line;\n	  while (<TMP>)\n	    {\n	 \
     $line = $_;\n	      if ($count ==1)\n		{\n		 \
 last;\n		}\n	      $count += 1;\n	    }\n	  \n	  \
\n	  $chain1 = substr($line,length($line)-3,1);\n	\
  \n	  close TMP;\n	  open(TMP,\"<$pdbfile2\");\n	\
  my $count = 0;\n	  while (<TMP>)\n	    {\n	     \
 $line = $_;\n	      if ($count ==1)\n		{\n		  las\
t;\n		}\n	      $count += 1;\n	    }\n	  $chain2 =\
 substr($line,length($line)-3,1);\n	  close TMP;\n\
\n	  $tmp_file=&vtmpnam();\n	  \n	  safe_system(\"\
runsara.py $pdbfile1 $chain1 $pdbfile2 $chain2 -s \
-o $tmp_file --limitation 5000 > /dev/null 2> /dev\
/null\") == 0 or die \"sara did not work $!\\n\";\\
n	  open(TMP,\"<$tmp_file\") or die \"cannot open \
the sara tmp file:$!\\n\";\n	  open(OUT,\">$outfil\
e\") or die \"cannot open the $outfile file:$!\\n\\
";\n	  \n	  my $switch = 0;\n	  my $seqNum = 0;\n	\
  foreach my $line (<TMP>)\n	    {\n	      next un\
less ($line=~/SARAALI/);\n	      if ($line=~/>/)\n\
		{\n		  $switch =0;\n		  print OUT \">seq$seqNum\\
\n\";\n		  $seqNum++;\n		}\n	      if ($switch < 2\
){\n		$switch++;\n		next;\n	      }\n	      \n	   \
   if ($line =~/REMARK\\s+SARAALI\\s+([^\\*]+)\\*/\
)\n		{\n		  my $string = $1;\n		  print OUT \"$str\
ing\\n\";\n		}\n	    }\n	  close TMP;\n	  close OU\
T;\n	  unlink($tmp_file);\n	}\n      }\n\nsub seq2\
tblastx_lib\n  {\n    my ($mode, $infile, $outfile\
)=@_;\n    my (%s, $method,$nseq);\n\n    $method=\
$mode;\n    &set_temporary_dir (\"set\",$infile,\"\
infile\");\n    %s=read_fasta_seq(\"infile\");\n\n\
\n    foreach $seq (keys(%s))\n      {\n	$slist[$s\
{$seq}{order}]=$s{$seq}{seq};\n	$sname[$s{$seq}{or\
der}]=$s{$seq}{name};\n	$slen[$s{$seq}{order}]=len\
gth ($s{$seq}{seq});\n      }\n    $nseq=$#sname+1\
;\n    open (F, \">outfile\");\n    print F \"! TC\
_LIB_FORMAT_01\\n\";\n    print F \"$nseq\\n\";\n \
   for ($a=0; $a<$nseq;$a++)\n      {\n	print F \"\
$sname[$a] $slen[$a]  $slist[$a]\\n\"\n      }\n  \
  close (F);\n    &safe_system (\"formatdb -i infi\
le -p F\");\n    &safe_system (\"blastall -p tblas\
tx -i infile -d infile -m 7 -S1>blast.output\");\n\
\n    ncbi_tblastx_xml2lib_file (\"outfile\", file\
2string (\"blast.output\"));\n    &set_temporary_d\
ir (\"unset\",$mode, $method, \"outfile\",$outfile\
);\n    myexit ($EXIT_SUCCESS);\n    }\nsub seq2tb\
lastpx_lib\n  {\n    my ($mode, $infile, $outfile)\
=@_;\n    my (%s, $method,$nseq);\n    $method=$mo\
de;\n    &set_temporary_dir (\"set\",$infile,\"inf\
ile\");\n    %s=read_fasta_seq(\"infile\");\n\n   \
 foreach $seq (keys(%s))\n      {\n	$slist[$s{$seq\
}{order}]=$s{$seq}{seq};\n	$sname[$s{$seq}{order}]\
=$s{$seq}{name};\n	$slen[$s{$seq}{order}]=length (\
$s{$seq}{seq});\n      }\n    $nseq=$#sname+1;\n  \
  open (F, \">outfile\");\n    print F \"! TC_LIB_\
FORMAT_01\\n\";\n    print F \"$nseq\\n\";\n    fo\
r ($a=0; $a<$nseq;$a++)\n      {\n	print F \"$snam\
e[$a] $slen[$a]  $slist[$a]\\n\"\n      }\n    clo\
se (F);\n    &safe_system(\"t_coffee -other_pg seq\
_reformat -in infile -output tblastx_db1 > tblastx\
db\");\n    &safe_system (\"formatdb -i tblastxdb \
-p T\");\n    &safe_system (\"blastall -p blastp -\
i tblastxdb -d tblastxdb -m7 >blast.output\");\n  \
  ncbi_tblastpx_xml2lib_file (\"outfile\", file2st\
ring (\"blast.output\"), %s);\n    &set_temporary_\
dir (\"unset\",$mode, $method, \"outfile\",$outfil\
e);\n    myexit ($EXIT_SUCCESS);\n    }\n\n\n\n\n\\
n\nsub file2head\n      {\n	my $file = shift;\n	my\
 $size = shift;\n	my $f= new FileHandle;\n	my $lin\
e;\n	open ($f,$file);\n	read ($f,$line, $size);\n	\
close ($f);\n	return $line;\n      }\nsub file2tai\
l\n      {\n	my $file = shift;\n	my $size = shift;\
\n	my $f= new FileHandle;\n	my $line;\n\n	open ($f\
,$file);\n	seek ($f,$size*-1, 2);\n	read ($f,$line\
, $size);\n	close ($f);\n	return $line;\n      }\n\
\n\nsub vtmpnam\n      {\n	my $r=rand(100000);\n	m\
y $f=\"file.$r.$$\";\n	while (-e $f)\n	  {\n	    $\
f=vtmpnam();\n	  }\n	push (@TMPFILE_LIST, $f);\n	r\
eturn $f;\n      }\n\nsub myexit\n  {\n    my $cod\
e=@_[0];\n    if ($CLEAN_EXIT_STARTED==1){return;}\
\n    else {$CLEAN_EXIT_STARTED=1;}\n    ### ONLY \
BARE EXIT\n    exit ($code);\n  }\nsub set_error_l\
ock\n    {\n      my $name = shift;\n      my $pid\
=$$;\n\n\n      &lock4tc ($$,\"LERROR\", \"LSET\",\
 \"$$ -- ERROR: $name $PROGRAM\\n\");\n      retur\
n;\n    }\nsub set_lock\n  {\n    my $pid=shift;\n\
    my $msg= shift;\n    my $p=getppid();\n    &lo\
ck4tc ($pid,\"LLOCK\",\"LRESET\",\"$p$msg\\n\");\n\
  }\nsub unset_lock\n   {\n\n    my $pid=shift;\n \
   &lock4tc ($pid,\"LLOCK\",\"LRELEASE\",\"\");\n \
 }\nsub shift_lock\n  {\n    my $from=shift;\n    \
my $to=shift;\n    my $from_type=shift;\n    my $t\
o_type=shift;\n    my $action=shift;\n    my $msg;\
\n\n    if (!&lock4tc($from, $from_type, \"LCHECK\\
", \"\")){return 0;}\n    $msg=&lock4tc ($from, $f\
rom_type, \"LREAD\", \"\");\n    &lock4tc ($from, \
$from_type,\"LRELEASE\", $msg);\n    &lock4tc ($to\
, $to_type, $action, $msg);\n    return;\n  }\nsub\
 isshellpid\n  {\n    my $p=shift;\n    if (!lock4\
tc ($p, \"LLOCK\", \"LCHECK\")){return 0;}\n    el\
se\n      {\n	my $c=lock4tc($p, \"LLOCK\", \"LREAD\
\");\n	if ( $c=~/-SHELL-/){return 1;}\n      }\n  \
  return 0;\n  }\nsub isrootpid\n  {\n    if(lock4\
tc (getppid(), \"LLOCK\", \"LCHECK\")){return 0;}\\
n    else {return 1;}\n  }\nsub lock4tc\n	{\n	  my\
 ($pid,$type,$action,$value)=@_;\n	  my $fname;\n	\
  my $host=hostname;\n\n	  if ($type eq \"LLOCK\")\
{$fname=\"$LOCKDIR/.$pid.$host.lock4tcoffee\";}\n	\
  elsif ( $type eq \"LERROR\"){ $fname=\"$LOCKDIR/\
.$pid.$host.error4tcoffee\";}\n	  elsif ( $type eq\
 \"LWARNING\"){ $fname=\"$LOCKDIR/.$pid.$host.warn\
ing4tcoffee\";}\n\n	  if ($debug_lock)\n	    {\n	 \
     print STDERR \"\\n\\t---lock4tc(tcg): $action\
 => $fname =>$value (RD: $LOCKDIR)\\n\";\n	    }\n\
\n	  if    ($action eq \"LCHECK\") {return -e $fna\
me;}\n	  elsif ($action eq \"LREAD\"){return file2\
string($fname);}\n	  elsif ($action eq \"LSET\") {\
return string2file ($value, $fname, \">>\");}\n	  \
elsif ($action eq \"LRESET\") {return string2file \
($value, $fname, \">\");}\n	  elsif ($action eq \"\
LRELEASE\")\n	    {\n	      if ( $debug_lock)\n		{\
\n		  my $g=new FileHandle;\n		  open ($g, \">>$fn\
ame\");\n		  print $g \"\\nDestroyed by $$\\n\";\n\
		  close ($g);\n		  safe_system (\"mv $fname $fna\
me.old\");\n		}\n	      else\n		{\n		  unlink ($fn\
ame);\n		}\n	    }\n	  return \"\";\n	}\n\nsub fil\
e2string\n	{\n	  my $file=@_[0];\n	  my $f=new Fil\
eHandle;\n	  my $r;\n	  open ($f, \"$file\");\n	  \
while (<$f>){$r.=$_;}\n	  close ($f);\n	  return $\
r;\n	}\nsub string2file\n    {\n    my ($s,$file,$\
mode)=@_;\n    my $f=new FileHandle;\n\n    open (\
$f, \"$mode$file\");\n    print $f  \"$s\";\n    c\
lose ($f);\n  }\n\nBEGIN\n    {\n      srand;\n\n \
     $SIG{'SIGUP'}='signal_cleanup';\n      $SIG{'\
SIGINT'}='signal_cleanup';\n      $SIG{'SIGQUIT'}=\
'signal_cleanup';\n      $SIG{'SIGILL'}='signal_cl\
eanup';\n      $SIG{'SIGTRAP'}='signal_cleanup';\n\
      $SIG{'SIGABRT'}='signal_cleanup';\n      $SI\
G{'SIGEMT'}='signal_cleanup';\n      $SIG{'SIGFPE'\
}='signal_cleanup';\n\n      $SIG{'SIGKILL'}='sign\
al_cleanup';\n      $SIG{'SIGPIPE'}='signal_cleanu\
p';\n      $SIG{'SIGSTOP'}='signal_cleanup';\n    \
  $SIG{'SIGTTIN'}='signal_cleanup';\n      $SIG{'S\
IGXFSZ'}='signal_cleanup';\n      $SIG{'SIGINFO'}=\
'signal_cleanup';\n\n      $SIG{'SIGBUS'}='signal_\
cleanup';\n      $SIG{'SIGALRM'}='signal_cleanup';\
\n      $SIG{'SIGTSTP'}='signal_cleanup';\n      $\
SIG{'SIGTTOU'}='signal_cleanup';\n      $SIG{'SIGV\
TALRM'}='signal_cleanup';\n      $SIG{'SIGUSR1'}='\
signal_cleanup';\n\n\n      $SIG{'SIGSEGV'}='signa\
l_cleanup';\n      $SIG{'SIGTERM'}='signal_cleanup\
';\n      $SIG{'SIGCONT'}='signal_cleanup';\n     \
 $SIG{'SIGIO'}='signal_cleanup';\n      $SIG{'SIGP\
ROF'}='signal_cleanup';\n      $SIG{'SIGUSR2'}='si\
gnal_cleanup';\n\n      $SIG{'SIGSYS'}='signal_cle\
anup';\n      $SIG{'SIGURG'}='signal_cleanup';\n  \
    $SIG{'SIGCHLD'}='signal_cleanup';\n      $SIG{\
'SIGXCPU'}='signal_cleanup';\n      $SIG{'SIGWINCH\
'}='signal_cleanup';\n\n      $SIG{'INT'}='signal_\
cleanup';\n      $SIG{'TERM'}='signal_cleanup';\n \
     $SIG{'KILL'}='signal_cleanup';\n      $SIG{'Q\
UIT'}='signal_cleanup';\n\n      our $debug_lock=$\
ENV{\"DEBUG_LOCK\"};\n\n\n\n\n      foreach my $a \
(@ARGV){$CL.=\" $a\";}\n      if ( $debug_lock ){p\
rint STDERR \"\\n\\n\\n********** START PG: $PROGR\
AM *************\\n\";}\n      if ( $debug_lock ){\
print STDERR \"\\n\\n\\n**********(tcg) LOCKDIR: $\
LOCKDIR $$ *************\\n\";}\n      if ( $debug\
_lock ){print STDERR \"\\n --- $$ -- $CL\\n\";}\n\\
n\n\n\n    }\nsub flush_error\n  {\n    my $msg=sh\
ift;\n    return add_error ($EXIT_FAILURE,$$, $$,g\
etppid(), $msg, $CL);\n  }\nsub add_error\n  {\n  \
  my $code=shift;\n    my $rpid=shift;\n    my $pi\
d=shift;\n    my $ppid=shift;\n    my $type=shift;\
\n    my $com=shift;\n\n    $ERROR_DONE=1;\n    lo\
ck4tc ($rpid, \"LERROR\",\"LSET\",\"$pid -- ERROR:\
 $type\\n\");\n    lock4tc ($$, \"LERROR\",\"LSET\\
", \"$pid -- COM: $com\\n\");\n    lock4tc ($$, \"\
LERROR\",\"LSET\", \"$pid -- STACK: $ppid -> $pid\\
\n\");\n\n    return $code;\n  }\nsub add_warning\\
n  {\n    my $rpid=shift;\n    my $pid =shift;\n  \
  my $command=shift;\n    my $msg=\"$$ -- WARNING:\
 $command\\n\";\n    print STDERR \"$msg\";\n    l\
ock4tc ($$, \"LWARNING\", \"LSET\", $msg);\n  }\n\\
nsub signal_cleanup\n  {\n    print dtderr \"\\n**\
** $$ (tcg) was killed\\n\";\n    &cleanup;\n    e\
xit ($EXIT_FAILURE);\n  }\nsub clean_dir\n  {\n   \
 my $dir=@_[0];\n    if ( !-d $dir){return ;}\n   \
 elsif (!($dir=~/tmp/)){return ;}#safety check 1\n\
    elsif (($dir=~/\\*/)){return ;}#safety check 2\
\n    else\n      {\n	`rm -rf $dir`;\n      }\n   \
 return;\n  }\nsub cleanup\n  {\n    #print stderr\
 \"\\n----tc: $$ Kills $PIDCHILD\\n\";\n    #kill \
(SIGTERM,$PIDCHILD);\n    my $p=getppid();\n    $C\
LEAN_EXIT_STARTED=1;\n\n\n\n    if (&lock4tc($$,\"\
LERROR\", \"LCHECK\", \"\"))\n      {\n	my $ppid=g\
etppid();\n	if (!$ERROR_DONE)\n	  {\n	    &lock4tc\
($$,\"LERROR\", \"LSET\", \"$$ -- STACK: $p -> $$\\
\n\");\n	    &lock4tc($$,\"LERROR\", \"LSET\", \"$\
$ -- COM: $CL\\n\");\n	  }\n      }\n    my $warni\
ng=&lock4tc($$, \"LWARNING\", \"LREAD\", \"\");\n \
   my $error=&lock4tc($$,  \"LERROR\", \"LREAD\", \
\"\");\n    #release error and warning lock if roo\
t\n\n    if (isrootpid() && ($warning || $error) )\
\n      {\n\n	print STDERR \"**************** Summ\
ary *************\\n$error\\n$warning\\n\";\n\n	&l\
ock4tc($$,\"LERROR\",\"RELEASE\",\"\");\n	&lock4tc\
($$,\"LWARNING\",\"RELEASE\",\"\");\n      }\n\n\n\
    foreach my $f (@TMPFILE_LIST)\n      {\n	if (-\
e $f){unlink ($f);}\n      }\n    foreach my $d (@\
TMPDIR_LIST)\n      {\n	clean_dir ($d);\n      }\n\
    #No More Lock Release\n    #&lock4tc($$,\"LLOC\
K\",\"LRELEASE\",\"\"); #release lock\n\n    if ( \
$debug_lock ){print STDERR \"\\n\\n\\n********** E\
ND PG: $PROGRAM ($$) *************\\n\";}\n    if \
( $debug_lock ){print STDERR \"\\n\\n\\n**********\
(tcg) LOCKDIR: $LOCKDIR $$ *************\\n\";}\n \
 }\nEND\n  {\n\n    &cleanup();\n  }\n\nsub blast_\
com2new_blast_com\n    {\n      my $com=shift;\n	 \
 if ($com=~/formatdb/)\n	    {\n	      $com=~s/for\
matdb/makeblastdb/;\n	      $com=~s/\\-i/\\-in/;\n\
	      if ($com =~/pF/){$com=~s/\\-pF/\\-dbtype nu\
cl/;}\n	      if ($com =~/p F/){$com=~s/\\-p F/\\-\
dbtype nucl/;}\n	      $com=\"$com -logfile /dev/n\
ull\";\n	      return $com;\n	    }\n	  else {retu\
rn $com;}\n\n    }\nsub safe_system\n{\n  my $com=\
shift;\n  my $ntry=shift;\n  my $ctry=shift;\n  my\
 $pid;\n  my $status;\n  my $ppid=getppid();\n  if\
 ($com eq \"\"){return 1;}\n\n  if ( ($com=~/^blas\
t/) ||($com=~/^formatdb/)){$com=&blast_com2new_bla\
st_com($com);}\n\n  if (($pid = fork ()) < 0){retu\
rn (-1);}\n  if ($pid == 0)\n    {\n      set_lock\
($$, \" -SHELL- $com (tcg)\");\n      if( $debug_g\
eneric_method ) { printf \"~ exec: %s\\n\", $com; \
}\n      exec ($com);\n      if( $debug_generic_me\
thod ) { printf \"~ exitcode: %s\\n\", $?; }\n    \
}\n  else\n    {\n      lock4tc ($$, \"LLOCK\", \"\
LSET\", \"$pid\\n\");#update parent\n      $PIDCHI\
LD=$pid;\n    }\n  if ($debug_lock){printf STDERR \
\"\\n\\t .... safe_system (fasta_seq2hmm)  p: $$ c\
: $pid COM: $com\\n\";}\n\n  waitpid ($pid,WTERMSI\
G);\n\n  shift_lock ($pid,$$, \"LWARNING\",\"LWARN\
ING\", \"LSET\");\n\n  if ($? == $EXIT_FAILURE || \
lock4tc($pid, \"LERROR\", \"LCHECK\", \"\"))\n    \
{\n      if ($ntry && $ctry <$ntry)\n	{\n\n	  add_\
warning ($$,$$,\"$com failed [retry: $ctry out of \
$ntry]\");\n	  lock4tc ($pid, \"LRELEASE\", \"LERR\
OR\", \"\");\n	  #if ($com=~/EBI/){$com=~s/EBI/NCB\
I/;}\n	  #elsif ($com=~/NCBI/){$com=~s/NCBI/EBI/;}\
\n\n	  return safe_system ($com, $ntry, ++$ctry);\\
n	}\n      elsif ($ntry == -1)\n	{\n	  if (!shift_\
lock ($pid, $$, \"LERROR\", \"LWARNING\", \"LSET\"\
))\n	    {\n	      add_warning ($$,$$,\"$com faile\
d\");\n	    }\n	  else\n	    {\n	      lock4tc ($p\
id, \"LRELEASE\", \"LERROR\", \"\");\n	    }\n	  r\
eturn $?;}\n      else\n	{\n	  if (!shift_lock ($p\
id,$$, \"LERROR\",\"LERROR\", \"LSET\"))\n	    {\n\
	      myexit(add_error ($EXIT_FAILURE,$$,$pid,get\
ppid(), \"UNSPECIFIED system\", $com));\n	    }\n	\
}\n    }\n  return $?;\n}\n\nsub check_configurati\
on\n    {\n      my @l=@_;\n      my $v;\n      fo\
reach my $p (@l)\n	{\n\n	  if   ( $p eq \"EMAIL\")\
\n	    {\n	      if ( !($EMAIL=~/@/))\n		{\n		add_\
warning($$,$$,\"Could Not Use EMAIL\");\n		myexit(\
add_error ($EXIT_FAILURE,$$,$$,getppid(),\"EMAIL\"\
,\"$CL\"));\n	      }\n	    }\n	  elsif( $p eq \"I\
NTERNET\")\n	    {\n	      if ( !&check_internet_c\
onnection())\n		{\n		  myexit(add_error ($EXIT_FAI\
LURE,$$,$$,getppid(),\"INTERNET\",\"$CL\"));\n		}\\
n	    }\n	  elsif( $p eq \"wget\")\n	    {\n	     \
 if (!&pg_is_installed (\"wget\") && !&pg_is_insta\
lled (\"curl\"))\n		{\n		  myexit(add_error ($EXIT\
_FAILURE,$$,$$,getppid(),\"PG_NOT_INSTALLED:wget\"\
,\"$CL\"));\n		}\n	    }\n	  elsif( !(&pg_is_insta\
lled ($p)))\n	    {\n	      myexit(add_error ($EXI\
T_FAILURE,$$,$$,getppid(),\"PG_NOT_INSTALLED:$p\",\
\"$CL\"));\n	    }\n	}\n      return 1;\n    }\n\n\
$program=\"T-COFFEE (dev_brew@20170304_17:15)\";\n\
\n","*TC_METHOD_FORMAT_01\n******************gener\
ic_method.tc_method*************\n*\n*       Incor\
porating new methods in T-Coffee\n*       Cedric N\
otredame 26/08/08\n*\n****************************\
***************************\n*This file is a metho\
d file\n*Copy it and adapt it to your need so that\
 the method \n*you want to use can be incorporated\
 within T-Coffee\n********************************\
***********************\n*                  USAGE \
                             *\n******************\
*************************************\n*This file \
is passed to t_coffee via -in:\n*\n*	t_coffee -in \
Mgeneric_method.method\n*\n*	The method is passed \
to the shell using the following\n*call:\n*<EXECUT\
ABLE><PARAM1><IN_FLAG><seq_file><PARAM2><OUT_FLAG>\
<outname><PARAM>\n*\n*Conventions:\n*<FLAG_NAME> 	\
<TYPE>		<VALUE>\n*<VALUE>:	no_name 	<=> Replaced w\
ith a space\n*<VALUE>:	&nbsp	<=> Replaced with a s\
pace\n*\n*****************************************\
**************\n*                  ALN_MODE       \
                    *\n***************************\
****************************\n*pairwise   ->all Vs\
 all (no self )[(n2-n)/2aln]\n*m_pairwise ->all Vs\
 all (no self)[n^2-n]^2\n*s_pairwise ->all Vs all \
(self): [n^2-n]/2 + n\n*multiple   ->All the seque\
nces in one go\n*\nALN_MODE		pairwise\n*\n********\
***********************************************\n*\
                  OUT_MODE                        \
   *\n********************************************\
***********\n* mode for the output:\n*External met\
hods: \n* aln -> alignmnent File (Fasta or Clustal\
W Format)\n* lib-> Lib file (TC_LIB_FORMAT_01)\n*I\
nternal Methods:\n* fL -> Internal Function return\
ing a List (Librairie)\n* fA -> Internal Function \
returning an Alignmnent\n*\nOUT_MODE		aln\n*******\
************************************************\n\
*                  SEQ_TYPE                       \
    *\n*******************************************\
************\n*G: Genomic, S: Sequence, P: PDB, R:\
 Profile\n*Examples:\n*SEQTYPE	S	sequences against\
 sequences (default)\n*SEQTYPE	S_P	sequence agains\
t structure\n*SEQTYPE	P_P	structure against struct\
ure\n*SEQTYPE	PS	mix of sequences and structure	\n\
*\nSEQ_TYPE	S\n*\n\n******************************\
*************************\n*                COMMAN\
D LINE                         *\n*EXECUTABLE PARA\
M1 IN_FLAG OUT_FLAG PARAM             *\n*********\
**********************************************\n**\
**************************************************\
***\n*                  EXECUTABLE                \
         *\n**************************************\
*****************\n*name of the executable\n*passe\
d to the shell: executable\n*	\nEXECUTABLE	tc_gene\
ric_method.pl\n*\n********************************\
***********************\n*                  IN_FLA\
G                             *\n*****************\
**************************************\n*IN_FLAG\n\
*flag indicating the name of the in coming sequenc\
es\n*IN_FLAG S no_name ->no flag\n*IN_FLAG S &bnsp\
-in&bnsp -> \" -in \"\n*\nIN_FLAG		-infile=\n*\n**\
**************************************************\
***\n*                  OUT_FLAG                  \
         *\n**************************************\
*****************\n*OUT_FLAG\n*flag indicating the\
 name of the out-coming data\n*same conventions as\
 IN_FLAG\n*OUT_FLAG	S no_name ->no flag\n*if you w\
ant to redirect, pass the parameters via PARAM1\n*\
set OUT_FLAG to >\n*\nOUT_FLAG		-outfile=\n*\n****\
**************************************************\
*\n*                  PARAM_1                     \
         *\n**************************************\
*****************\n*<EXECUTABLE><PARAM1><IN_FLAG><\
seq_file><PARAM2><OUT_FLAG><outname><PARAM>\n*Para\
meters sent to the EXECUTABLE and specified *befor\
e* IN_FLAG \n*If there is more than 1 PARAM line, \
the lines are\n*concatenated\n*Command_line: @EP@P\
ARAM@-gapopen%e10%s-gapext%e20\n*	%s white space\n\
*	%e equal sign\n*\n*PARAM1	\n*\n*\n*\n***********\
********************************************\n*   \
               PARAM_2                            \
  *\n*********************************************\
**********\n*<EXECUTABLE><PARAM1><IN_FLAG><seq_fil\
e><PARAM2><OUT_FLAG><outname><PARAM>\n*Parameters \
sent to the EXECUTABLE and specified \n*after* IN_\
FLAG and *before* OUT_FLAG\n*If there is more than\
 1 PARAM line, the lines are\n*concatenated\n*\n*P\
ARAM1	\n*\n*\n************************************\
*******************\n*                  PARAM     \
                         *\n**********************\
*********************************\n*<EXECUTABLE><P\
ARAM1><IN_FLAG><seq_file><PARAM2><OUT_FLAG><outnam\
e><PARAM>\n*Parameters sent to the EXECUTABLE and \
specified *after* OUT_FLAG\n*If there is more than\
 1 PARAM line, the lines are\n*concatenated\n*\nPA\
RAM	-mode=seq_msa -method=clustalw\nPARAM   -OUTOR\
DER=INPUT -NEWTREE=core -align -gapopen=-15\n*\n**\
**************************************************\
***\n*                  END                       \
         *\n**************************************\
*****************\n","*TC_METHOD_FORMAT_01\n******\
*********clustalw_method.tc_method*********\nEXECU\
TABLE	clustalw\nALN_MODE		pairwise\nIN_FLAG		-INFI\
LE=\nOUT_FLAG		-OUTFILE=\nOUT_MODE		aln\nPARAM		-g\
apopen=-10\nSEQ_TYPE		S\n*************************\
************************\n","$VersionTag =        \
                                                  \
                                                  \
                       2.43;\nuse Env;\nuse FileHa\
ndle;\nuse Cwd;\nuse File::Path;\nuse Sys::Hostnam\
e;\nour $PIDCHILD;\nour $ERROR_DONE;\nour @TMPFILE\
_LIST;\nour $EXIT_FAILURE=1;\nour $EXIT_SUCCESS=0;\
\n\nour $REFDIR=getcwd;\nour $EXIT_SUCCESS=0;\nour\
 $EXIT_FAILURE=1;\n\nour $PROGRAM=\"extract_from_p\
db\";\nour $CL=$PROGRAM;\n\nour $CLEAN_EXIT_STARTE\
D;\nour $debug_lock=$ENV{\"DEBUG_LOCK\"};\nour $LO\
CKDIR=$ENV{\"LOCKDIR_4_TCOFFEE\"};\nif (!$LOCKDIR)\
{$LOCKDIR=getcwd();}\nour $ERRORDIR=$ENV{\"ERRORDI\
R_4_TCOFFEE\"};\nour $ERRORFILE=$ENV{\"ERRORFILE_4\
_TCOFFEE\"};\n&set_lock ($$);\nif (isshellpid(getp\
pid())){lock4tc(getppid(), \"LLOCK\", \"LSET\", \"\
$$\\n\");}\n      \nour $SILENT=\" >/dev/null 2>/d\
ev/null\";\nour $INTERNET=-1;\n\n\n\n\n\n\n\nour $\
BLAST_MAX_NRUNS=2;\nour $EXIT_SUCCESS=0;\nour $EXI\
T_FAILURE=1;\nour $CONFIGURATION=-1;\nour $REF_EMA\
IL=\"\";\nour $PROGRAM=\"extract_from_pdb\";\n\n\n\
my %onelett_prot=&fill_onelett_prot();\nmy %threel\
ett_prot=&fill_threelett_prot();\nmy %onelett_RNA=\
&fill_onelett_RNA();\nmy %threelett_RNA=&fill_thre\
elett_RNA();\nmy %onelett_DNA=&fill_onelett_DNA();\
\nmy %threelett_DNA=&fill_threelett_DNA();\n\n\n\n\
\n\nmy %onelett = (\n'P' => \\%onelett_prot,\n'D' \
=> \\%onelett_DNA,\n'R' => \\%onelett_RNA\n);\n\n\\
nmy %threelett = (\n'P' => \\%threelett_prot,\n'D'\
 => \\%threelett_DNA,\n'R' => \\%threelett_RNA\n);\
\n\n\n\n\n\n\n\nif($ARGV[0]=~/help/ ||$ARGV[0]=~/m\
an/ || $ARGV[0]=~/HELP/ || $ARGV[0]=~/Man/ || $ARG\
V[0] eq \"-h\"  || $ARGV[0] eq \"-H\"  )\n{die \"S\
YNTAX: extract_from_pdb Version $VersionTag	\n	Min\
imum:             [extract_from_pdb file] \n			   \
OR \n			     [... | extract_from_pdb]\n 	Flags (De\
fault setting on the first line)\n	   -version....\
...............[Returns the Version Number]\n     \
      -force.....................[Forces the file \
to be treated like a PDB file]\n                  \
                    [Regenerates the header and SE\
QRES fields]\n           -force_name..............\
..[Forces the file to be named after name]]\n     \
      -infile.....file...........[Flag can be omit\
ed]\n			              [File must be pdb or fro pgm\
]\n                                      [File can\
 also be compressed Z or gz]\n                    \
                  [In the case of a compressed fil\
e, you can omit the gz|Z extension]\n           -n\
etfile...................[File will be fetch from \
the net using wget]\n                             \
         [wget or curl must be installed]\n       \
                               [ftp://ftp.gnu.org/\
pub/gnu/wget/]\n                                  \
    [http://curl.haxx.se/]\n                      \
                [Must also be used to retrieve the\
 file from a local pdb copy (cf netaddress)]\n    \
       -netaddress................[Address used fo\
r the retrieving the netfile]\n                   \
                   [http://www.rcsb.org/pdb/cgi/ex\
port.cgi/%%.pdb.gz?format=PDB&pdbId=%%&compression\
=gz]\n                                      [http:\
//www.expasy.ch/cgi-bin/get-pdb-entry.pl?%%]\n    \
                                  [local -> will g\
et the file from pdb_dir (see pdb_dir)]\n         \
  -netcompression............[Extension if the net\
file comes compressed]\n                          \
            [gz]\n           -pdb_dir.............\
......[address of the repertory where the pdb is i\
nstalled]\n                                      [\
Supports standard ftp style installation OR every \
stru in DIR]\n                                    \
  [Give the ..../pdb/structure/ dir]\n            \
                          [If value omitted, the p\
g gets it from the env variable PDB_DIR]\n        \
   -netcompression_pg.........[gunzip]\n          \
 -is_pdb_name..........name.[Returns 1 if the name\
 is a PDB ID, 0 otherwise]\n           -model_type\
...........name.[Returns the model type if valid P\
DB name]\n           -is_released_pdb_name name.[R\
eturns 1 if the name corresponds to a released PDB\
 file]\n           -get_pdb_chains.....name...[Ret\
urns the list of chains corresponding to the entry\
]\n           -get_pdb_id.........name...[Returns \
the PDB id within the provided pdb file]\n        \
   -get_fugue_name.....name...[Turns a name into a\
 name valid for fugue]\n                          \
            [Uses the netaddress to do so]\n	   -c\
hain......FIRST..........[Extract the first chain \
only]\n		       A B C..........[Extract Several ch\
ains if needed]\n		       ALL............[Extract \
all the chains]	\n           -ligand.....ALL......\
......[Extract the ligands in the chain (HETATM)]\\
n                       <name1>,<name2>[Extract Al\
l the named lignds]\n	   -ligand_only.............\
..[Extract only the ligands]\n           -ligand_l\
ist...............[Extract the list of ligands]\n	\
   -coor.......<start>..<end>.[Coordinates of the \
fragment to extract]\n			              [Omit end t\
o include the Cter]\n           -num........absolu\
te.......[absolute: relative to the seq] \n       \
                file...........[file: relative to \
file]\n           -num_out....new............[new:\
 start 1->L]\n                       old..........\
..[old: keep the file coordinates]\n           -de\
lete.....<start>..<end>.[Delete from residue start\
 to residue end]\n	   -atom.......CA.............[\
Atoms to include, ALL for all of them]\n		       C\
A O N.........[Indicate several atoms if needed]\n\
	   -code.......3..............[Use the 1 letter c\
ode or the 3 letters code]\n	   -mode.......raw...\
.........[Output original pdb file]\n             \
          pdb............[Output something that lo\
oks like pdb]\n		       fasta..........[Output the\
 sequences in fasta format]\n		       simple......\
...[Output a format easy to parse in C ]\n        \
    -seq_field..ATOM...........[Field used to extr\
act the sequence]\n		       SEQRES.........[Use th\
e complete sequence]\n	   -seq....................\
...[Equivalent to  -mode fasta]\n	   -model......1\
..............[Chosen Model in an NMR file]\n     \
      -nodiagnostic..............[Switches Error M\
essages off]\n           -debug...................\
..[Sets the DEBUG ON]\n           -no_remote_pdb_d\
ir.........[Do not look for a remote file]\n      \
     -cache_pdb.................[Cache Value, defa\
ult is $HOME/.t_coffee/cache, other values: NO<=> \
No cache]\n\n      Environement Variables\n       \
    These variables can be set from the environeme\
nt\n           Command line values with the corres\
ponding flag superseed evironement value\n        \
   NO_REMOTE_PDB_DIR..........[Prevents the progra\
m from searching remote file: faster]\n           \
PDB_DIR....................[Indicates where PDB fi\
le must be fetched (localy)]\n\n	 PROBLEMS: please\
 contact cedric.notredame\\@europe.com\\n\";\n	 ex\
it ($EXIT_SUCCESS);\n}\n\n$np=0;\n$n_para=$#ARGV;\\
n$model=1;\n$pdb_dir=$ENV{'PDB_DIR'};if ($pdb_dir)\
{$pdb_dir.=\"/\";}\n$debug=$ENV{'DEBUG_EXTRACT_FRO\
M_PDB'};\n\n$no_remote_pdb_dir=$ENV{NO_REMOTE_PDB_\
DIR};\n$HOME=$ENV{'HOME'};\nif ( $ENV{CACHE_4_TCOF\
FEE})\n{$cache=$ENV{CACHE_4_TCOFFEE};}\nelse\n{\n \
   $cache=\"$HOME/.t_coffee/cache/\";\n}\n\n   \n$\
netaddress=\"http://www.rcsb.org/pdb/files/%%.pdb.\
gz\";\n$netcompression_pg=\"gunzip\";\n$netcompres\
sion=\"gz\";\n\nforeach ($np=0; $np<=$n_para; $np+\
+)\n  {        \n    $value=$ARGV[$np];\n   \n    \
if  ($np==0 && !($value=~/^-.*/))\n      { \n	$pdb\
_file= $ARGV[$np];\n      }\n    elsif ( !($value=\
~/^-.*/))\n      {\n	print \"@ARGV\";\n	die;\n    \
  } \n    \n    elsif ($value eq \"-nodiagnostic\"\
){$nodiagnostic=1;}\n    elsif ($value eq \"-force\
\")\n      {\n	$force_pdb=1;\n      }\n    elsif (\
$value eq \"-force_name\")\n      {\n	$force_name=\
$ARGV[++$np];\n	$force_pdb=1;\n      }\n    \n    \
elsif ($value eq \"-is_pdb_name\")\n      {\n	$pdb\
_file= $ARGV[++$np];	\n	$is_pdb_name=1;	\n      } \
\n    elsif ($value eq \"-is_released_pdb_name\")\\
n      {\n	$pdb_file= $ARGV[++$np];	\n	$is_release\
d_pdb_name=1;\n      }\n    elsif ($value eq \"-mo\
del_type\")\n      {\n	$pdb_file= $ARGV[++$np];	\n\
	$model_type=1;\n      }\n    elsif ($value eq \"-\
debug\")\n{\n	$debug=1;\n}\n    elsif ($value eq \\
"-get_pdb_chains\")\n{\n	$pdb_file= $ARGV[++$np];\\
n	$get_pdb_chains=1;\n}\n    elsif ($value eq \"-g\
et_pdb_ligands\")\n{\n	$get_pdb_ligands=1;\n}\n   \
 \n    elsif ($value eq \"-get_pdb_id\")\n{\n	$pdb\
_file= $ARGV[++$np];\n	$get_pdb_id=1;\n	\n}\n    \\
n    elsif ( $value eq \"-get_fugue_name\")\n{\n	$\
pdb_file= $ARGV[++$np];\n	$get_fugue_name=1;\n}\n \
   elsif ( $value eq \"-infile\")\n{\n       $pdb_\
file= $ARGV[++$np];\n} \n    elsif ($value eq \"-n\
etfile\")\n{\n	$netfile=1;\n	if ( !($ARGV[$np+1]=~\
/^-.*/)){$pdb_file= $ARGV[++$np];}\n}\n    elsif (\
  $value eq \"-num\")\n{\n       $numbering= $ARGV\
[++$np];\n}\n    elsif (  $value eq \"-num_out\")\\
n{\n       $numbering_out= $ARGV[++$np];\n}\n    e\
lsif ( $value eq \"-netaddress\")\n{\n	$netadress=\
$ARGV[++$np];\n}\n     \n    elsif ( $value eq \"-\
netcompression\")\n{\n	 $netcompression=$ARGV[++$n\
p];\n}\n    elsif ( $value eq \"-pdb_dir\")\n{\n	 \
if ( !($ARGV[$np+1]=~/^-.*/)){$pdb_dir= \"$ARGV[++\
$np]/\";}\n}\n     elsif ( $value eq \"-no_remote_\
pdb_dir\")\n{\n	$no_remote_pdb_dir=1;\n	if ( !($AR\
GV[$np+1]=~/^-.*/)){$pdb_dir= \"$ARGV[++$np]/\";}\\
n}\n    elsif ( $value eq \"-cache\")\n{\n	$cache=\
$ARGV[++$np];\n}\n    \n    elsif ($value eq \"-ne\
tcompression_pg\")\n{\n	  $netcompression_pg=$ARGV\
[++$np];\n}\n     elsif ($value eq \"-mode\")\n{\n\
       $MODE=$ARGV[++$np];\n}\n\n    elsif ( $valu\
e eq \"-model\")\n{\n       $model= $ARGV[++$np];\\
n}\n    elsif ($value eq \"-seq_field\" )\n{\n    \
   $seq_field= $ARGV[++$np];\n}   \n    elsif ($va\
lue eq \"-coor\" )\n{\n       $start= $ARGV[++$np]\
;\n  \n       if (($ARGV[$np+1] eq \"\") ||($ARGV[\
$np+1]=~/^-.*/)){$end=\"*\";} \n       else {$end=\
   $ARGV[++$np];}     \n       $coor_set=1;\n}\n  \
  elsif ($value eq \"-delete\" )\n{\n       $delet\
e_start= $ARGV[++$np];\n       $delete_end= $ARGV[\
++$np];\n       $delete_set=1;\n}\n    elsif  ($va\
lue eq \"-code\")\n{\n       $code= $ARGV[++$np];\\
n}\n    elsif  ($value eq \"-no_hetatm\")\n{\n    \
   $no_hetatm=1;\n}\n    elsif ($value eq \"-chain\
\")\n{\n       while (!($ARGV[$np+1] eq \"\") &&!(\
$ARGV[$np+1]=~/^-.*/))\n{\n	      ++$np;\n	      @\
c_chain=(@chain,  $ARGV[$np]);\n	      $hc_chain{$\
ARGV[$np]}=$#c_chain+1;\n}           \n}\n    elsi\
f ($value eq \"-atom\")\n{\n\n       while (!($ARG\
V[$np+1] eq \"\") && !($ARGV[$np+1]=~/^-.*/))\n{\n\
	      ++$np;\n	      $atom[$n_atom++]=  $ARGV[$np\
];\n	      $atom_list{$ARGV[$np]}=1;	      \n} \n \
      \n}\n    elsif ( $value eq \"-unfold\")\n{\n\
	$unfold=1;\n}\n    elsif ($value eq \"-seq\" ||$v\
alue eq \"-fasta\" )\n{\n       $MODE=\"fasta\";\n\
}\n    elsif ( $value eq \"-version\")\n{\n	print \
STDERR  \"\\nextract_from_pdb: Version $VersionTag\
\\n\";\n	&myexit ($EXIT_SUCCESS);\n}\n    elsif ( \
$value eq \"-ligand\")\n{\n	while (!($ARGV[$np+1] \
eq \"\") && !($ARGV[$np+1]=~/^-.*/))\n{\n	    ++$n\
p;\n	    $ligand=1;\n	    $ligand_list{$ARGV[$np]}\
=1;	      \n} \n	$hc_chain{'LIGAND'}=1;\n}\n    el\
sif ( $value eq \"-ligand_only\")\n{\n	$ligand_onl\
y=1;\n}\n}\nif ( $debug)\n{\n    print STDERR \"\\\
n[DEBUG:extract_from_pdb] NO_REMOTE_PDB_DIR: $no_r\
emote_pdb_dir\\n\";\n    print STDERR \"\\n[DEBUG:\
extract_from_pdb] PDB_DIR: $pdb_dir\\n\";\n}\n\n\n\
if ( $is_pdb_name)\n  {\n    if (&remote_is_pdb_na\
me($pdb_file))\n      {\n	print \"1\";\n      }\n \
   else\n      {\n	print \"0\";\n      }\n    exit\
 ($EXIT_SUCCESS);\n  }\n\nif ( $is_released_pdb_na\
me)\n  {\n    \n    if (&is_released($pdb_file))\n\
      {\n	print \"1\";\n      }\n    else\n      {\
\n	print \"0\";\n      }\n    exit ($EXIT_SUCCESS)\
;\n  }\nif ($model_type)\n  {\n   \n    printf \"%\
s\", &pdb2model_type($pdb_file);\n    exit ($EXIT_\
SUCCESS);\n    \n  }\n    \n\nif (!$force_name)\n{\
\n    $pdb_file=~/([^\\/]*)$/;\n    $force_name=$1\
;\n}\n\n$local_pdb_file=$pdb_file;\n\nif ( $debug)\
{print STDERR \"\\n[DEBUG: extract_from_pdb] Scan \
For $local_pdb_file\\n\";}\n\n$mem=$no_remote_pdb_\
dir;\n$no_remote_pdb_dir=1;\n$tmp_pdb_file=get_pdb\
_file ($local_pdb_file);\n\nif ( !-e $tmp_pdb_file\
 || $tmp_pdb_file eq \"\")\n  {\n    $local_pdb_fi\
le=$pdb_file;\n    ($local_pdb_file, $suffix_chain\
)=&pdb_name2name_and_chain($local_pdb_file);\n\n  \
  if ($local_pdb_file)\n      {\n	if ( $debug){pri\
nt STDERR \"\\nSplit $pdb_file into $local_pdb_fil\
e and $suffix_chain \\n\";}\n	$tmp_pdb_file=get_pd\
b_file ($local_pdb_file);\n	if ( $tmp_pdb_file ne \
\"\")\n	  {\n	    @c_chain=();\n	    @c_chain=($su\
ffix_chain);\n	    %hc_chain=();\n	    $hc_chain{$\
suffix_chain}=1;\n	  }\n      }\n  }\n\n$no_remote\
_pdb_dir=$mem;\nif ($no_remote_pdb_dir==0)\n  {\n \
   \n    if ( !-e $tmp_pdb_file || $tmp_pdb_file e\
q \"\")\n      {\n	\n	$local_pdb_file=$pdb_file;\n\
	($local_pdb_file, $suffix_chain)=&pdb_name2name_a\
nd_chain($local_pdb_file);\n	if ($local_pdb_file)\\
n	  {\n	    \n	    if ( $debug){print STDERR \"\\n\
Split $pdb_file into $local_pdb_file and $suffix_c\
hain \\n\";}\n	    \n	    $tmp_pdb_file=get_pdb_fi\
le ($local_pdb_file);    \n	    \n	    if ( $tmp_p\
db_file ne \"\")\n	      {\n		@c_chain=();\n		@c_c\
hain=($suffix_chain);\n		%hc_chain=();\n		$hc_chai\
n{$suffix_chain}=1;\n	      }\n	  }\n      }\n  }\\
n\nif ( $debug){print STDERR \"\\n$pdb_file copied\
 into ##$tmp_pdb_file##\\n\";}\n\nif ( !-e $tmp_pd\
b_file || $tmp_pdb_file eq \"\")\n{\n	if ($is_pdb_\
name)\n{\n	    print \"0\\n\"; exit ($EXIT_SUCCESS\
);\n}\n	else\n{\n  \n	    print \"\\nEXTRACT_FROM_\
PDB: NO RESULT for $pdb_file\\n\";\n	    &myexit (\
$EXIT_SUCCESS);	\n}\n}\n\n\n\n\n%molecule_type=&pd\
bfile2chaintype($tmp_pdb_file);\nif ( $debug){prin\
t STDERR \"\\n\\tSequence Type determined\\n\";}\n\
\n$pdb_id=&get_pdb_id ($tmp_pdb_file);\nif ( $debu\
g){print STDERR \"\\n\\tID: $pdb_id (for $tmp_pdb_\
file)\\n\";}\n\nif ( $pdb_id eq \"\"){$pdb_id=$for\
ce_name;}\n\n@f_chain=&get_chain_list ($tmp_pdb_fi\
le);\nif ( $debug){print STDERR \"\\n\\tChain_list\
:@f_chain\\n\";}\n\nif ( $get_pdb_chains)\n{\n    \
print \"@f_chain\\n\";\n    &myexit ($EXIT_SUCCESS\
);\n}\nif ( $get_pdb_ligands)\n{\n    %complete_li\
gand_list=&get_ligand_list ($tmp_pdb_file);\n    p\
rint $complete_ligand_list{\"result\"};\n    &myex\
it ($EXIT_SUCCESS);\n}\n\nelsif ( $get_pdb_id ||$g\
et_fugue_name )\n{\n    if    (@c_chain && $c_chai\
n[0] eq \"FIRST\"){$pdb_id=$pdb_id.$f_chain[0];}\n\
    elsif (@c_chain && $c_chain[0] ne \" \"){$pdb_\
id=$pdb_id.$c_chain[0];}\n    \n    print \"$pdb_i\
d\\n\";\n    &myexit ($EXIT_SUCCESS);\n    \n}\nel\
sif ( $is_pdb_name)\n{\n    printf \"1\\n\";\n    \
&myexit ($EXIT_SUCCESS);\n}\n\n\n\n$structure_file\
=vtmpnam();\n\nif ( $debug){print STDERR \"\\n\\tC\
heck_point #1: $tmp_pdb_file  $structure_file\\n\"\
;}\n\n$INFILE=vfopen (\"$tmp_pdb_file\", \"r\"); \\
n$TMP=vfopen (\"$structure_file\", \"w\");\n\n$pri\
nt_model=1;\n$in_model=0;\n\nif ( $debug){print ST\
DERR \"\\n\\tCheck_point #2\\n\";}\nwhile ( <$INFI\
LE>)\n{\n  my $first_model=0;\n  $line=$_;\n\n  if\
 ( !$first_model && ($line =~/^MODEL\\s*(\\d*)/))\\
n    {\n      $first_model=$1;\n      if ($model==\
1){$model=$first_model;}\n    }\n  \n  if (($line \
=~/^MODEL\\s*(\\d*)/))\n    {\n      if ($1==$mode\
l)\n	{\n	  $in_model=1;\n	  $print_model=1;\n	  $i\
s_nmr=1;\n	}\n      elsif ( $in_model==0)\n	{\n	  \
$print_model=0;\n	}\n      elsif ( $in_model==1)\n\
	{\n	  last;\n	}\n    }\n  if ($print_model){print\
 $TMP $line;}  \n}\nclose ($TMP);\nclose ($INFILE)\
;\n\nif ( $debug){print STDERR \"\\n\\tCheck_point\
 #3\\n\";}	\n\n  if ($numbering eq \"\"){$numberin\
g=\"absolute\";}\n  if ($numbering_out eq \"\"){$n\
umbering_out=\"new\";}\n\n  if ( $delete_set && $c\
oor_set) {die \"-delete and -coor are mutually exc\
lusive, sorry\\n\";}\n  if ( $n_atom==0){$atom_lis\
t[$n_atom++]=\"ALL\";$atom_list{$atom_list[0]}=1;}\
\n  if ( $seq_field eq \"\"){$seq_field=\"ATOM\";}\
\n  \n  if ( $MODE eq \"\"){$MODE=\"pdb\";}\n  els\
if ( $MODE eq \"simple\" && $code==0){$code=1;}\n\\
n  if ( $code==0){$code=3;}\n\n\nif ($f_chain[0] e\
q \" \"){$hc_chain{' '}=1;$c_chain[0]=\" \";}\nels\
if (!@c_chain){$hc_chain{FIRST}=1;$c_chain[0]=\"FI\
RST\";}#make sure the first chain is taken by defa\
ult\n\nif    ($hc_chain{ALL}) \n{\n      @c_chain=\
@f_chain;\n      foreach $e (@c_chain){$hc_chain{$\
e}=1;}\n}\nelsif($hc_chain{FIRST})\n{\n	@c_chain=(\
$f_chain[0]);\n	$hc_chain{$f_chain[0]}=1;\n}\n\n\n\
$MAIN_HOM_CODE=&get_main_hom_code ($structure_file\
);\n$INFILE=vfopen ($structure_file, \"r\");\n\n\n\
if ( $MODE eq \"raw_pdb\" || $MODE eq \"raw\")\n{\\
n    while (<$INFILE>)\n{	print \"$_\";}\n    clos\
e ( $INFILE);\n    &myexit($EXIT_SUCCESS);\n}    \\
nif ( $MODE eq \"raw4fugue\" )\n{\n    while (<$IN\
FILE>)\n{	\n	$l=$_;\n	if ($l=~/^SEQRES/)\n{\n	    \
\n	    $c= substr($l,11,1);\n	    if ($hc_chain {$\
c}){print \"$l\";}\n}\n	elsif ( $l=~/^ATOM/)\n{\n	\
    $c=substr($l,21,1);\n	    if ($hc_chain {$c}){\
print \"$l\";}\n}\n}\n    close ( $INFILE);\n    &\
myexit($EXIT_SUCCESS);\n}    \n\nif ( $MODE eq \"p\
db\")\n{\n\n    $read_header=0;\n    while (<$INFI\
LE>) \n{\n	    $line=$_;\n	    if    ($line =~ /^H\
EADER/){print \"$line\";$read_header=1;}\n}\n    c\
lose ($INFILE);\n\n    if (!$read_header)\n{\n	pri\
nt \"HEADER    UNKNOWN                            \
     00-JAN-00   $force_name\\n\";\n}\n\n    $INFI\
LE=vfopen ($structure_file, \"r\");\n    \n    pri\
nt \"COMPND   1 CHAIN:\";\n    $last=pop(@c_chain)\
;\n    foreach $c ( @c_chain){ print \" $c,\";}\n \
   if ( $last eq \" \"){print \" NULL;\\n\";}\n   \
 else \n{\n      print \" $last;\\n\";\n}\n    @c_\
chain=(@c_chain, $last);\n    \n    print \"REMARK\
 Output of the program extract_from_pdb (Version $\
VersionTag)\\n\";\n    print \"REMARK Legal PDB fo\
rmat not Guaranteed\\n\";\n    print \"REMARK This\
 format is not meant to be used in place of the PD\
B format\\n\";\n    print \"REMARK The header refe\
rs to the original entry\\n\";\n    print \"REMARK\
 The sequence from the original file has been take\
n in the field: $seq_field\\n\";\n    print \"REMA\
RK extract_from_pdb, 2001, 2002, 2003, 2004, 2005 \
2006 (c) CNRS and Cedric Notredame\\n\";   \n    i\
f ( $coor_set)\n{\n       print \"REMARK Partial c\
hain: Start $start End $end\\n\";\n}\n    if ( $is\
_nmr)\n{\n       print \"REMARK NMR structure: MOD\
EL $model\\n\";\n}\n   \n    if ( $n_atom!=0)\n{\n\
       print \"REMARK Contains Coordinates of: \";\
\n       foreach $a (@atom){print \"$a \";}\n     \
  print \"\\n\";\n}  \n}\n\n\n\n\nmy $residue_inde\
x = -999;\nmy $old_c = \"TemporaryChain\";\n\nwhil\
e (<$INFILE>) \n{\n	$line=$_;\n\n\n	if ($line =~ /\
^SEQRES/)\n{\n\n		@field=/(\\S*)\\s*/g;\n\n		$c= s\
ubstr($_,11,1);\n\n		\n		$l=$#field;\n		for ($a=4;\
 $a<$#field ;)\n{\n			if (!$onelett{$molecule_type\
{$c}}->{$field[$a]})\n{\n				splice @field, $a, 1;\
\n}\n			else \n{\n				$a++;\n}\n}\n	\n		if ( $c ne\
 $in_chain)\n{\n			$pdb_chain_list[$n_pdb_chains]=\
$c;\n			$pdb_chain_len [$n_pdb_chains]=$len;\n			$\
in_chain=$c;\n			$n_pdb_chains++;\n}\n	\n		for ( $\
a=4; $a<$#field;$a++)\n{\n			$complete_seq{$c}[$co\
mplete_seq_len{$c}++]=$field[$a];\n}\n}\n    elsif\
 ( $line=~/^ATOM/ || ($line=~/^HETATM/ && &is_aa(s\
ubstr($line,17,3),substr($line,21,1)) && !$no_heta\
tm))\n{\n\n	 \n    $RAW_AT_ID=$AT_ID=substr($line,\
12,4);\n	$RES_ID=&is_aa(substr($line,17,3),substr(\
$line,21,1));\n	$CHAIN=substr($line,21,1);\n\n    \
$RES_NO=substr($line,22,4);\n	$HOM_CODE=substr ($l\
ine, 26, 1);\n	$TEMP=substr($line,60,6);\n	\n	$TEM\
P=~s/\\s//g;\n        $AT_ID=~s/\\s//g;\n	$RES_ID=\
~s/\\s//g;\n        $RES_NO=~s/\\s//g;\n		\n	if ( \
$HOM_CODE ne $MAIN_HOM_CODE){next;}\n	elsif ( $alr\
eady_read2{$CHAIN}{$RES_ID}{$AT_ID}{$RES_NO}){next\
;}\n	else{$already_read2{$CHAIN}{$RES_ID}{$AT_ID}{\
$RES_NO}=1;}\n	\n	\n	if ($coor_set && $numbering e\
q \"file\" && $residue_index ne $RES_NO)\n{\n	    \
\n	    if ( $RES_NO<=$start){$real_start{$CHAIN}++\
;}\n	    if ( $RES_NO<=$end){$real_end{$CHAIN}++;}\
\n}\n	elsif ($numbering eq \"absolute\")\n{\n	    \
$real_start{$CHAIN}=$start;\n	    $real_end{$CHAIN\
}=$end;\n}\n\n        $KEY=\"ALL\";\n        if ( \
$CHAIN ne $in_atom_chain)\n{\n	    \n	  $pdb_atom_\
chain_list[$n_pdb_atom_chains]=$c;\n	  $pdb_atom_c\
hain_len [$n_pdb_atom_chains]=$len;\n	  $in_atom_c\
hain=$c;\n	  $n_pdb_atom_chains++;\n}\n	\n	if ( $r\
esidue_index ne $RES_NO)\n{\n	     $residue_index \
= $RES_NO;\n	     $atom_seq{$CHAIN}[$atom_seq_len{\
$CHAIN}++]=$RES_ID;;\n}\n}\n\n}\nclose ($INFILE);\\
n\n\n\n\n\n\n$INFILE=vfopen ($structure_file, \"r\\
");\nforeach $c (@c_chain)\n{\n\n	if    ( $seq_fie\
ld eq \"SEQRES\"){@pdb_seq=@{$complete_seq{$c}};}\\
n	elsif ( $seq_field eq \"ATOM\")  {@pdb_seq=@{$at\
om_seq{$c}};}\n	\n\n	$full_length=$l=$#pdb_seq+1;\\
n		\n	if ( $real_end{$c}==\"*\"){$real_end{$c}=$fu\
ll_length;}\n	if ( $coor_set)\n{	   \n\n	   if ( $\
real_end{$c} < $l){splice @pdb_seq, $real_end{$c},\
 $l;}\n	   if ( $real_start{$c} < $l){splice @pdb_\
seq, 0, $real_start{$c}-1;}	  	   \n	   $l=$#pdb_s\
eq;\n}\n\n	elsif ( $delete_set)\n{\n	   splice @pd\
b_seq, $delete_start, $delete_end-$delete_start+1;\
\n	   $l=$#pdb_seq;\n}\n	\n	$new_fasta_name=\"$pdb\
_id$c\";\n	if ( $coor_set)\n{\n	   if ( $n_pdb_cha\
ins==0){$new_fasta_name=\"$new_fasta_name$c\";}\n	\
   $new_fasta_name= $new_fasta_name.\"\\_$start\\_\
$end\";\n}\n	   \n	if ( $MODE eq \"pdb\")\n{\n	   \
$nl=1;\n	   $n=0;\n	   \n	   foreach $res ( @pdb_s\
eq)\n		{\n		if ( !$n)\n		{\n		\n		 printf \"SEQRES\
 %3d %1s %4d  \", $nl,$c, $l;\n		 $nl++;\n	}\n	   \
  $res=~s/\\s//g;\n	     \n	     if ($code==1){ pr\
intf \"%3s \",$onelett{$molecule_type{$c}}->{$res}\
;}\n	     elsif  ($code==3){ printf \"%3s \",$res}\
;\n	     \n	     $n++;		  \n	     if ( $n==13){$n=\
0;print \"\\n\";}\n}\n	  if ( $n!=0){print \"\\n\"\
; $n=0;}\n}\n	elsif ( $MODE eq \"simple\")\n{\n	  \
print \"# SIMPLE_PDB_FORMAT\\n\";\n	  if ( $new_fa\
sta_name eq \" \"){$new_fasta_name=\"dummy_name\";\
}\n	  print \">$new_fasta_name\\n\";\n\n	  foreach\
 $res ( @pdb_seq)\n{\n	      print \"$onelett{$mol\
ecule_type{$c}}->{$res}\";\n}\n	  print \"\\n\";\n\
}\n	elsif ( $MODE eq \"fasta\")\n{\n	  $n=0;\n	  p\
rint \">$new_fasta_name\\n\";\n	  \n	  foreach $re\
s ( @pdb_seq)\n{\n\n	      print \"$onelett{$molec\
ule_type{$c}}->{$res}\";\n              $n++;\n	  \
    if ( $n==60){print \"\\n\"; $n=0;}\n}\n	  prin\
t \"\\n\"; \n}\n}\n\nif ( $MODE eq \"fasta\")\n{\n\
     &myexit($EXIT_SUCCESS);\n  \n}\n\n  \n  $char\
count=0;\n  $inchain=\"BEGIN\";\n  $n=0;\n  while \
(<$INFILE>) \n{\n    $line=$_;\n     \n    if ($li\
ne =~/^ATOM/  ||  ($line=~/^HETATM/))\n{\n	$line_h\
eader=\"UNKNWN\";\n	$RES_ID=substr($line,17,3);\n	\
$chain = substr($line,21,1);\n\n	if ($line =~/^ATO\
M/)\n{\n	    $line_header=\"ATOM\";\n	    $RES_ID=\
(&is_aa($RES_ID,$chain))?&is_aa($RES_ID,$chain):$R\
ES_ID;\n}\n	elsif ($line=~/^HETATM/ && ($ligand_li\
st {$RES_ID} ||$ligand_list {'ALL'} || !&is_aa($RE\
S_ID,$chain)))\n{\n	    $line_header=\"HETATM\";\n\
}\n	elsif ($line=~/^HETATM/ && (&is_aa($RES_ID,$ch\
ain) && !$no_hetatm))\n{\n	    $line_header=\"ATOM\
\";\n	    $RES_ID=&is_aa($RES_ID,$chain);\n}\n	els\
e\n{\n	    next;\n}\n\n	\n\n	$X=substr($line,30,8)\
;     \n	$Y=substr($line,38,8);\n	$Z=substr($line,\
46,8);\n	$TEMP=substr($line,60,6);\n	\n	$RAW_AT_ID\
=$AT_ID=substr($line,12,4);\n	$CHAIN=substr($line,\
21,1);\n	$RES_NO=substr($line,22,4);\n	$HOM_CODE=s\
ubstr ($line, 26, 1);\n	\n	$X=~s/\\s//g;\n	$Y=~s/\\
\s//g;\n	$Z=~s/\\s//g;\n	$TEMP=~s/\\s//g;\n	\n	$AT\
_ID=~s/\\s//g;\n	$RES_ID=~s/\\s//g;\n	$RES_NO=~s/\\
\s//g;\n\n	\n	if ( $HOM_CODE ne $MAIN_HOM_CODE){ne\
xt;}\n	elsif ( $already_read{$CHAIN}{$RES_ID}{$AT_\
ID}{$RES_NO}){next;}\n	else{$already_read{$CHAIN}{\
$RES_ID}{$AT_ID}{$RES_NO}=1;}\n	\n	$KEY=\"ALL\";\n\
\n      	if ( $RES_NO ==0){$start_at_zero=1;}\n\n	\
$RES_NO+=$start_at_zero;    \n	\n	if ( $current_ch\
ain ne $CHAIN)\n{\n	    $current_chain=$CHAIN;\n	 \
   $pos=$current_residue=0;\n	    $offset=($coor_s\
et)?($real_start{$CHAIN}-1):0;\n	    if    ( $seq_\
field eq \"SEQRES\"){@ref_seq=@{$complete_seq{$CHA\
IN}};}\n	    elsif ( $seq_field eq \"ATOM\")  {@re\
f_seq=@{$atom_seq{$CHAIN}};}\n}\n	\n	if ($current_\
residue != $RES_NO)\n{\n	    $current_residue=$RES\
_NO;\n	    if    ( $seq_field eq \"SEQRES\"){$pos=\
$current_residue;}\n	    elsif ( $seq_field eq \"A\
TOM\"){$pos++;}\n}\n	\n	\n	if ($n_atom==0 || $atom\
_list{$AT_ID}==1 || $atom_list{$KEY}==1)\n{ 	\n	  \
  \n	    $do_it=(!@c_chain || $hc_chain{$CHAIN} ||\
$hc_chain{'LIGAND'} );\n	    \n	    $do_it= ($do_i\
t==1) && ($coor_set==0 ||($pos>=$real_start{$CHAIN\
} && $pos<=$real_end{$CHAIN}));\n	    $do_it= ($do\
_it==1) && ($delete_set==0 || $pos<$delete_start |\
|$pos>$delete_end );\n	    if ($ligand==0 && $line\
_header eq \"HETATM\" ){$do_it=0;}\n	    if ($liga\
nd_only==1 && $line_header eq \"ATOM\" ){$do_it=0;\
}\n	    if ($ligand==1 && $line_header eq \"HETATM\
\" && $ligand_list{$RES_ID}==0 && $ligand_list{\"A\
LL\"}==0){$do_it=0;} \n	    \n	    \n	    if ( $do\
_it)\n{\n		$n++;\n		$out_pos=$pos;\n		\n	       if\
 ( $delete_set)\n{\n		  if ( $out_pos< $delete_sta\
rt){;}\n		  else {$offset=$delete_end-$delete_star\
t;}\n}       \n	       \n	       if ( $numbering_o\
ut eq \"new\"){$out_pos-=$offset;}\n	       elsif \
( $numbering_out eq \"old\"){$out_pos=$RES_NO;}\n	\
       \n       \n	       \n	       if ( $code==1)\
{$RES_ID=$onelett{$molecule_type{$c}}->{$RES_ID};}\
\n	    \n	       if ($unfold)\n{\n		   $unfolded_x\
+=5;\n		   $X=$unfolded_x;\n		   $Y=0;\n		   $Z=0;\
\n		   $float=1;\n}\n	       else\n{\n		   $float=\
3;\n}\n\n	       if ( $MODE eq \"pdb\")\n{\n		   p\
rintf \"%-6s%5d %-4s %3s %s%4d    %8.3f%8.3f%8.3f \
 1.00 %5.2f\\n\",$line_header, $n, $RAW_AT_ID,$RES\
_ID,$CHAIN,$out_pos, $X, $Y, $Z,$TEMP;		  \n}\n	  \
     elsif ( $MODE eq \"simple\")\n{\n		    if ( $\
RES_ID eq \"\"){$RES_ID=\"X\";}\n		  printf \"%-6s\
 %5s %s %2s %4d    %8.3f %8.3f %8.3f\\n\",$line_he\
ader, $AT_ID, $RES_ID,($CHAIN eq\"\" || $CHAIN eq \
\" \")?\"A\":$CHAIN,$out_pos, $X, $Y, $Z,$TEMP;\n}\
\n\n}\n}\n}\n}\nprint \"\\n\";\nclose($INFILE);\n\\
n\nif ( $error ne \"\") \n{$error=$error.\"\\nDiag\
nostic:    SEQRES and the residues in ATOM are pro\
bably Incompatible\\n\";\n    $error=$error.  \"Re\
comendation: Rerun with '-fix 1' in order to ignor\
e the SEQRES sequences\\n\";\n}\nif (!$nodiagnosti\
c){print STDERR $error;}\n&myexit ( $EXIT_SUCCESS)\
;\n\nsub is_released \n  {\n    my ($r);\n    my $\
in=@_[0];\n    my $name=&remote_is_pdb_name ($in);\
\n    my $hold=&remote_is_on_hold($in);\n    \n   \
 $r=($name && !$hold)?1:0;\n    return $r;\n  }\ns\
ub remote_is_pdb_name \n{\n    my $in=@_[0];\n    \
my ($ref_file, $pdb);\n    my ($value,$value1,$val\
ue2);\n    my $max=2;\n    \n    $ref_file=\"$cach\
e/pdb_entry_type.txt\";\n    \n    if ( $in=~/[^\\\
w\\d\\:\\_]/){return 0;}\n    elsif ($no_remote_pd\
b_dir==1)\n      {\n	my $pdbdir=$ENV{'PDB_DIR'};\n\
	\n	my $r1=\"$pdbdir/derived_data/pdb_entry_type.t\
xt\";\n	my $r2=$ref_file;\n	if    (-e $r1){$ref_fi\
le=$r1;}\n	elsif (-e $r2){$ref_file=$r2;}\n	else\n\
	  {\n	    my $p=substr ($in,0, 4);\n	    add_warn\
ing (\"Cannot find pdb_entry_type.txt;  $p is assu\
med to be valid; add ftp://ftp.wwpdb.org/pub/pdb/d\
erived_data/pdb_entry_type.txt in $cache to check \
name status\");\n	  }\n      }\n    elsif ( !-e $r\
ef_file || (-M $ref_file)>$max || -z $ref_file)\n \
     {\n	&url2file(\"ftp://ftp.wwpdb.org/pub/pdb/d\
erived_data/pdb_entry_type.txt\", $ref_file);\n   \
   }\n    $pdb=substr ($in,0, 4);\n    chomp(($val\
ue1=`grep -c $pdb $ref_file`));\n    $pdb=lc($pdb)\
;\n    chomp(($value2=`grep -c $pdb $ref_file`));\\
n    $value=($value1 || $value2)?1:0;\n    $value=\
($value>0)?1:0;\n    \n    return $value;\n  }\n\n\
sub pdb2model_type\n{\n    my $in=@_[0];\n    my (\
$ref_file, $pdb);\n    my ($value, $ret);\n\n    i\
f ( $in=~/[^\\w\\d\\:\\_]/){return 0;}\n    $ref_f\
ile=\"$cache/pdb_entry_type.txt\";\n    \n    if (\
 !-e $ref_file || (-M $ref_file)>2 || -z $ref_file\
)\n      {\n	&url2file(\"ftp://ftp.wwpdb.org/pub/p\
db/derived_data/pdb_entry_type.txt\", $ref_file);\\
n      }\n    $pdb=substr ($in,0, 4);\n    $pdb=lc\
($pdb);\n    \n    chomp(($value=`grep $pdb $ref_f\
ile`));\n    \n    $value=~/^\\S+\\s+\\S+\\s+(\\S+\
)/;\n    $ret=$1;\n    if ( $ret eq\"\"){return \"\
UNKNOWN\";}\n    \n    return $ret;\n  }\nsub remo\
te_is_on_hold\n  {\n    my $in=@_[0];\n    my ($re\
f_file, $pdb);\n    my ($value1, $value2,$value);\\
n    \n    if ($no_rmote_pdb==1){return 0;}\n    e\
lsif ( $in=~/[^\\w\\d\\:\\_]/){return 0;}\n    $re\
f_file=\"$cache/unreleased.xml\";\n    \n    if ( \
!-e $ref_file || (-M $ref_file)>2 || -z $ref_file)\
\n      {\n	&url2file(\"http://www.rcsb.org/pdb/re\
st/getUnreleased\",$ref_file);\n      }\n    \n   \
 $pdb=substr ($in,0, 4);\n    chomp(($value1=`grep\
 -c $pdb $ref_file`));\n    $pdb=lc($pdb);\n    ch\
omp(($value2=`grep -c $pdb $ref_file`));\n    $val\
ue=($value1 || $value2)?1:0;\n    $value=($value>0\
)?1:0;\n    return $value;\n  }\nsub is_pdb_file\n\
{\n    my @arg=@_;\n\n    if ( !-e $arg[0]){return\
 0;}\n    \n    $F=vfopen ($arg[0], \"r\");\n    w\
hile ( <$F>)\n{\n	if (/^HEADER/)\n{\n	    close $F\
;\n	    return 1;\n}\n	elsif ( /^SEQRES/)\n{\n	   \
 close $F;\n	    return 1;\n}\n	elsif ( /^ATOM/)\n\
{\n	    close $F;\n	    return 1;\n}\n}\n    retur\
n 0;\n}\nsub get_pdb_id\n{\n    my $header_file=@_\
[0];\n    my $id;\n    my $F= new FileHandle;\n   \
 \n    \n    $F=vfopen (\"$header_file\", \"r\");\\
n\n    while ( <$F>)\n      {\n	if ( /HEADER/)\n	 \
 {\n	    if ($debug){print \"$_\";}\n	    $id=subs\
tr($_,62,4 );\n	    return $id;\n	  }\n      }\n  \
  close ($F);\n    \n    return \"\";\n}\n\nsub ge\
t_ligand_list\n{\n    my $pdb_file=@_[0];\n    my \
$chain;\n    my $ligand;\n    my %complete_ligand_\
list;\n    \n\n    $F=vfopen ($pdb_file, \"r\");\n\
    while ( <$F>)\n{\n	if ( /^HETATM/)\n{\n	    $l\
ine=$_;\n	    $chain=substr($line,21,1);\n	    $li\
gand=substr($line,17,3);\n	    \n	    if (!$comple\
te_ligand_list{$chain}{$ligand})\n{\n		\n		$comple\
te_ligand_list{\"result\"}.=\"CHAIN $chain LIGAND \
$ligand\\n\";\n		$complete_ligand_list{$chain}{$li\
gand}=1;\n}\n}\n}\n    close ($F);\n    return %co\
mplete_ligand_list;\n}\n\nsub get_chain_list \n{\n\
    my $header_file;\n    my @chain_list;\n    my \
@list;\n    my $n_chains;\n    my %chain_hasch;\n \
   my $pdb_file=@_[0];\n    my $c;\n    my %hasch;\
\n    my $chain;\n  \n    \n    $F=vfopen ($pdb_fi\
le, \"r\");\n    while ( <$F>)\n{\n\n\n	if (/SEQRE\
S\\s+\\d+\\s+(\\S+)/)\n	  {\n	    $chain = substr(\
$_,11,1);$chain=~s/\\s//g;if ( $chain eq \"\"){$ch\
ain=\" \";}\n	    if (!$hasch{$chain}){$hasch{$cha\
in}=1;push @chain_list, $chain;}\n	  }\n	if (/^ATO\
M/ || /^HETATM/)\n	  {\n	    $chain = substr($_,21\
,1); $chain=~s/\\s//g;if ( $chain eq \"\"){$chain=\
\" \";}\n	    if (!$hasch{$chain}){$hasch{$chain}=\
1;push @chain_list, $chain;}\n	  }\n      }\n\n\nc\
lose ($F);\nif (!@chain_list)\n  {\n    @chain_lis\
t=(\"A\");\n  }\n\n\nreturn @chain_list;\n}\n\nsub\
 token_is_in_list\n{\n\n    my @list=@_;\n    my $\
a;\n    \n    for ($a=1; $a<=$#list; $a++)\n{\n	if\
 ( $list[$a] eq $list[0]){return $a;}\n}\n}\n\nsub\
 pdb_name2name_and_chain \n{\n    my $pdb_file=@_[\
0];\n    my $pdb_file_in;\n    my @array;\n    my \
$chain;\n    my $c;\n\n    $pdb_file_in=$pdb_file;\
\n\n    $pdb_file=~/^(.{4})/;$pdb_id=$1;\n    @arr\
ay=($pdb_file=~/([\\w])/g);\n  \n  \n    $chain=uc\
 ($array[4]);\n    $chain=($chain eq \"\")?\"FIRST\
\":$chain;\n    \n    return ( $pdb_id, $chain);\n\
\n    if ( $#array==3){return ($pdb_id, \"FIRST\")\
;}\n    elsif ( $#array<4){ return ($pdb_id, \"\")\
;}\n    else {return ( $pdb_id, $chain);}\n      \\
n    \n    \n}\nsub get_main_hom_code \n{\n    my \
$pdb_file=@_[0];\n    my %hom, $n, $best, $best_h;\
\n    open (F, $pdb_file);\n    while (<F>)\n{\n	i\
f ( $_=~/^ATOM/)\n{\n	    $h=substr ($_,26, 1);\n	\
    $n=++$hom{$h};\n	    if ($n>$best)\n{\n		$best\
=$n;\n		$best_h=$h;\n}\n}\n}\n    close (F);\n    \
return $best_h;\n}\n\n\nsub get_pdb_file \n{\n    \
my ($pdb_file_in)=(@_);\n    my $result;\n    my @\
letter;\n    my @chain;\n    my $v;\n    my $pdb_f\
ile=$pdb_file_in;\n\n    $pdb_file=($pdb_file_in=~\
/\\S+_S_(\\S+)/)?$1:$pdb_file_in;\n    \n    if ($\
no_remote_pdb_dir==0)\n      {\n	$no_remote_pdb_di\
r=1;\n	$result=get_pdb_file3 ($pdb_file);\n	$no_re\
mote_pdb_dir=0;\n	if ( $result){return $result;}\n\
	else\n	  {\n	    \n	    lc ($pdb_file);\n	    $re\
sult=get_pdb_file3($pdb_file);\n	    return  $resu\
lt;\n	  }\n      }\n    else\n      {\n	return get\
_pdb_file3 ($pdb_file);\n      }\n    \n  }\n\nsub\
 get_pdb_file3 \n{\n    my $pdb_file_in=@_[0];\n  \
  my $result;\n    my @letter;\n    my @chain;\n  \
  my $lcfile;\n    my $ucfile;\n    my $pdb_file=$\
pdb_file_in;\n    \n    $lcfile=lc $pdb_file;\n   \
 $ucfile=uc $pdb_file;\n\n    if ( ($result=get_pd\
b_file2 ($pdb_file))){return $result;}\n    \n\n  \
  if ($lcfile ne $pdb_file && ($result=get_pdb_fil\
e2 ($lcfile))){return $result;}\n    if ($ucfile n\
e $pdb_file && ($result=get_pdb_file2 ($ucfile))){\
return $result;}\n    \n   \n    \n    return \"\"\
;\n}\nsub get_pdb_file2\n{\n    my $pdb_file=@_[0]\
;\n    my $return_value;\n    \n    $return_value=\
\"\";\n    \n    if ( ($result=get_pdb_file1 ($pdb\
_file))){$return_value=$result;}\n    elsif ( !($p\
db_file=~/\\.pdb/) && !($pdb_file=~/\\.PDB/))\n{\n\
	if ( ($result=get_pdb_file1 (\"$pdb_file.pdb\")))\
{$return_value=$result;}\n	elsif ( ($result=get_pd\
b_file1 (\"$pdb_file.PDB\"))){$return_value=$resul\
t;}\n\n	elsif ( ($result=get_pdb_file1 (\"pdb$pdb_\
file.pdb\"))){$return_value=$result;}	\n	elsif ( (\
$result=get_pdb_file1 (\"pdb$pdb_file.PDB\"))){$re\
turn_value=$result;}\n	elsif ( ($result=get_pdb_fi\
le1 (\"PDB$pdb_file.PDB\"))){$return_value=$result\
;}\n	elsif ( ($result=get_pdb_file1 (\"PDB$pdb_fil\
e.pdb\"))){$return_value=$result;}\n	\n	\n	elsif (\
 ($result=get_pdb_file1 (\"$pdb_file.ent\"))){$ret\
urn_value=$result;}\n	elsif ( ($result=get_pdb_fil\
e1 (\"pdb$pdb_file.ent\"))){$return_value=$result;\
}\n	elsif ( ($result=get_pdb_file1 (\"PDB$pdb_file\
.ent\"))){$return_value=$result;}\n\n	elsif ( ($re\
sult=get_pdb_file1 (\"$pdb_file.ENT\"))){$return_v\
alue=$result;}\n	elsif ( ($result=get_pdb_file1 (\\
"pdb$pdb_file.ENT\"))){$return_value=$result;}\n	e\
lsif ( ($result=get_pdb_file1 (\"PDB$pdb_file.ENT\\
"))){$return_value=$result;}\n	\n	\n	\n}\n    retu\
rn $return_value;\n}\n    \nsub get_pdb_file1\n{\n\
    my ($pdb_file)=(@_);\n    my $return_value;\n \
   \n\n    $return_value=\"\";\n    if ( ($result=\
get_pdb_file0 ($pdb_file))){$return_value=$result;\
}\n    elsif ( ($result=get_pdb_file0 (\"$pdb_file\
.Z\"))){$return_value=$result;}\n    elsif ( ($res\
ult=get_pdb_file0 (\"$pdb_file.gz\"))){$return_val\
ue=$result;}\n    elsif ( ($result=get_pdb_file0 (\
\"$pdb_file.GZ\"))){$return_value=$result;}\n    r\
eturn $return_value;\n}\nsub get_pdb_file0 \n{ \n \
   my ($pdb_file, $attempt)=(@_);\n    my $pdb_fil\
e=@_[0];\n    my $tmp_pdb_file;    \n    my $retur\
n_value;\n\n    if ( !$attempt){$attempt=1;}\n    \
\n    $local_pdb_file=\"$pdb_file\";\n    if ( $lo\
cal_pdb_file eq \"\")\n{\n	$tmp_pdb_file=vtmpnam()\
;\n	open F, \">$tmp_pdb_file\";\n	\n	while (<STDIN\
>){print F \"$_\";}\n	close (F);\n	\n	if (-e $tmp_\
pdb_file && &is_pdb_file ( $local_pdb_file))\n{ret\
urn $tmp_pdb_file;}\n}\n\n    $local_pdb_file=\"$p\
db_file\";\n    &debug_print (\"\\nTry access loca\
l file: $local_pdb_file\");\n    \n    $local_pdb_\
file=&check_pdb_file4compression ($local_pdb_file)\
;\n    if ( -e $local_pdb_file && (&is_pdb_file ($\
local_pdb_file) || $force_pdb))\n{\n	&debug_print \
( \"\\n\\tIs in Current Dir\");\n	$tmp_pdb_file=vt\
mpnam();\n	`cp $local_pdb_file $tmp_pdb_file`;\n	r\
eturn $tmp_pdb_file;\n}\n    else\n{\n	&debug_prin\
t (\"\\n\\tFile Not in Current Dir\");\n}\n\n    i\
f ($pdb_file=~/^pdb/||$pdb_file=~/^PDB/){$pdb_div=\
substr ($pdb_file, 4, 2);}\n    else\n{\n	  $pdb_d\
iv=substr ($pdb_file, 1, 2);\n}\n    $local_pdb_fi\
le=\"$pdb_dir/$pdb_div/$pdb_file\";\n    $local_pd\
b_file=&check_pdb_file4compression ( $local_pdb_fi\
le);\n    &debug_print (\"\\nTry access file From \
PDB_DIR: $local_pdb_file\");\n    if ($pdb_dir && \
-e $local_pdb_file && &is_pdb_file ($local_pdb_fil\
e))\n{\n	&debug_print ( \"\\n\\tIs in Local PDB DI\
R\");\n	$tmp_pdb_file=vtmpnam();\n	`cp $local_pdb_\
file $tmp_pdb_file`;\n	return $tmp_pdb_file;\n}\n\\
n    $local_pdb_file=\"$pdb_dir/$pdb_file\";\n    \
$local_pdb_file=&check_pdb_file4compression ( $loc\
al_pdb_file);\n    &debug_print (\"\\nTry access f\
ile From PDB_DIR: local_pdb_file\");\n    if ($pdb\
_dir && -e $local_pdb_file && &is_pdb_file ($local\
_pdb_file))\n{\n	&debug_print ( \"\\n\\tIs in Loca\
l PDB DIR\");\n	$tmp_pdb_file=vtmpnam();\n	`cp $lo\
cal_pdb_file $tmp_pdb_file`;\n	return $tmp_pdb_fil\
e;\n}\n\n    $local_pdb_file=\"$pdb_dir$pdb_file\"\
;\n    $local_pdb_file=&check_pdb_file4compression\
 ( $local_pdb_file);\n    &debug_print (\"\\nTry a\
ccess file From PDB_DIR: $local_pdb_file\");\n    \
if ($pdb_dir && -e $local_pdb_file && &is_pdb_file\
 ($local_pdb_file))\n{\n	&debug_print ( \"\\n\\tIs\
 in Local PDB DIR\");\n	$tmp_pdb_file=vtmpnam();\n\
	`cp $local_pdb_file $tmp_pdb_file`;\n	return $tmp\
_pdb_file;\n}\n    else\n{&debug_print ( \"\\n\\tN\
ot In Local Pdb Dir\");}\n\n    if ($cache ne \"NO\
\" && $cache ne \"no\")\n{\n\n	$local_pdb_file=\"$\
cache/$pdb_file\";\n	$local_pdb_file=&check_pdb_fi\
le4compression ( $local_pdb_file);\n	&debug_print(\
\"\\nTry access file From Cache: $local_pdb_file\"\
);\n	if (-e $local_pdb_file && &is_pdb_file ($loca\
l_pdb_file))\n{\n	    &debug_print ( \"\\n\\tIs in\
 T-Coffee Cache\");\n	    $tmp_pdb_file=vtmpnam();\
\n	    `cp $local_pdb_file $tmp_pdb_file`;\n	    r\
eturn $tmp_pdb_file;\n}\n	else{&debug_print ( \"\\\
n\\tNot in Cache Dir\");}\n}\n\nif (!$no_remote_pd\
b_dir) \n  {\n    my $value=&is_released ($pdb_fil\
e);\n    my $return_value=\"\";\n    if ($value==1\
)\n      {\n	\n	&debug_print (\"\\n***************\
**************************************\\nTry Remot\
e Access for $pdb_file\");\n	$tmp_pdb_file=vtmpnam\
();\n	$netcommand=$netaddress;\n	$netcommand=~s/%%\
/$pdb_file/g;\n	&url2file(\"$netcommand\", \"$tmp_\
pdb_file.$netcompression\");\n	&debug_print(\"\\nR\
EMOTE: $netcommand\\n\");\n	\n	$compressed_tmp_fil\
e_name=\"$tmp_pdb_file.$netcompression\";\n	\n	if \
($netcompression && -B $compressed_tmp_file_name)\\
n	  {\n	    my $r;\n	    &debug_print (\"\\n\\tFil\
e Found Remotely\");\n	    if (($r=safe_system ( \\
"$netcompression_pg $compressed_tmp_file_name\")!=\
$EXIT_SUCCESS) && $attempts<5)\n	      {\n		&debug\
_print (\"\\n\\tProper Download Failed Try again\"\
);\n		unlink $compressed_tmp_file_name;\n		print \\
"\\nFailed to Download $compressed_tmp_file_name. \
New Attempt $attempt/5\\n\";\n		return &get_pdb_fi\
le0($pdb_file, $attempt+1);\n	      }\n	    elsif \
($r== $EXIT_SUCCESS)\n	      {\n		&debug_print (\"\
\\n\\tProper Download Succeeded \");\n		$return_va\
lue=$tmp_pdb_file;\n	      }\n	    else\n	      {\\
n		&debug_print (\"\\n\\tProper Download Failed \"\
);\n		&debug_print (\"\\nFile Not Found Remotely\"\
);\n		unlink $compressed_tmp_file_name;\n	      }\\
n	  }\n	else\n	  {\n\n	    &debug_print (\"\\nFile\
 Not Found Remotely\");\n	    unlink $compressed_t\
mp_file_name;\n	  }\n	#Update cache if required\n	\
if ($cache ne \"no\" && $cache ne \"update\" && -e\
 $return_value)\n	  {\n	    `cp $return_value $cac\
he/$pdb_file.pdb`;\n	    #`t_coffee -other_pg clea\
n_cache.pl -file $pdb_file.pdb -dir $cache`;\n	  }\
\n      }\n    &debug_print (\"\\nRemote Download \
Finished\");\n    return $return_value;\n  }\nretu\
rn \"\";\n}\n\nsub check_pdb_file4compression \n{\\
n    my $file=@_[0];\n    my $tmp;\n    my $r;\n  \
  \n    $tmp=&vtmpnam();\n    if (-e $tmp){unlink \
$tmp;}\n    \n    $file=~s/\\/\\//\\//g;\n    if  \
  (-B $file && ($file=~/\\.Z/)) {`cp $file $tmp.Z`\
;`rm $tmp`;`gunzip $tmp.Z $SILENT`;$r=$tmp;}\n    \
elsif (-B $file && ($file=~/\\.gz/)){`cp $file $tm\
p.gz`;`gunzip $tmp.gz $SILENT`;return $r=$tmp;}\n \
   elsif (-B $file ){`cp $file $tmp.gz`;`gunzip $t\
mp.gz $SILENT`;$r=$tmp;}\n    elsif ( -e $file ) {\
$r= $file;}\n    elsif ( -e \"$file.gz\" ){ `cp $f\
ile.gz $tmp.gz`;`gunzip     $tmp.gz $SILENT`;$r=$t\
mp;}    \n    elsif ( -e \"$file.Z\") {`cp $file.Z\
  $tmp.Z`; `gunzip $tmp.Z $SILENT`;$r=$tmp;}\n    \
else  {$r= $file;}\n\n    if ( -e \"$tmp.Z\"){unli\
nk \"$tmp.Z\";}\n    if ( -e \"$tmp.gz\"){unlink \\
"$tmp.gz\";}\n    \n    return $r;\n    \n}\n\n\n\\
n\n\n    \n\n\n\n\n\n\n\nsub vfopen \n{\n    my $f\
ile=@_[0];\n    my $mode=@_[1];\n    my $tmp;\n   \
 my $F = new FileHandle;\n    \n    \n    $tmp=$fi\
le;\n	\n    \n    if ( $mode eq \"r\" && !-e $file\
){ myexit(flush_error (\"Cannot open file $file\")\
);}\n    elsif ($mode eq \"w\"){$tmp=\">$file\";}\\
n    elsif ($mode eq \"a\"){$tmp=\">>$file\";}\n  \
  \n    \n    open ($F,$tmp);\n    return $F;\n}\n\
sub debug_print\n{\n    my $message =@_[0];\n    i\
f ($debug){print STDERR \"NO_REMOTE_PDB_DIR: $no_r\
emote_pdb_dir - $message [DEBUG:extract_from_pdb]\\
";}\n    return;\n}\nsub is_aa \n{\n    my ($aa, $\
chain) =@_;\n\n    my $one;\n    my $trhee;\n    \\
n    if ( $onelett{$molecule_type{$chain}}->{$aa} \
eq 'X' || !$onelett{$molecule_type{$chain}}->{$aa}\
 ){return '';}\n    else\n      {\n	$one=$onelett{\
$molecule_type{$chain}}->{$aa};\n\n	$three=$threel\
ett{$molecule_type{$chain}}->{$one};\n	\n\n	return\
 $three;\n      }\n  }\n\n\n\n\n\nsub url2file\n{\\
n    my ($address, $out, $wget_arg, $curl_arg)=(@_\
);\n    my ($pg, $flag, $r, $arg, $count);\n    \n\
    if (!$CONFIGURATION){&check_configuration (\"w\
get\", \"INTERNET\", \"gzip\");$CONFIGURATION=1;}\\
n    \n    if (&pg_is_installed (\"wget\"))   {$pg\
=\"wget\"; $flag=\"-O\";$arg=$wget_arg;}\n    elsi\
f (&pg_is_installed (\"curl\")){$pg=\"curl\"; $fla\
g=\"-o\";$arg=$curl_arg;}\n    return safe_system \
(\"$pg $flag$out $address >/dev/null 2>/dev/null\"\
);\n\n}\n\n\n\n\nsub pdbfile2chaintype\n  {\n    m\
y $file=@_[0];\n    my %ct;\n    my $F;\n    \n   \
 $F=vfopen ($file, \"r\");\n    while (<$F>)\n    \
  {\n	my $line=$_;\n	if ($line =~/^ATOM/)\n	  {\n	\
    my $C=substr($line,21,1);\n	    if (!$ct{$C})\\
n	      {	\n		my $r=substr($line,17,3);\n		$r=~s/\\
\s+//;\n		if (length ($r)==1){$ct{$C}=\"R\";}\n		e\
lsif (length ($r)==2){$ct{$C}=\"D\";}\n		elsif (le\
ngth ($r)==3){$ct{$C}=\"P\";}\n		else \n		  {\n		 \
   myexit(flush_error(\"ERROR: Could not read RES_\
ID field in file $file\"));\n		  }\n	      }\n	  }\
\n      }\n    close ($F);\n    return %ct;\n  }\n\
   \n    \n\n\n\nsub fill_threelett_RNA\n{\n\n	my \
%threelett=(\n	'A', '  A',\n	'T', '  T',\n	'U', ' \
 U',\n	'C', '  C',\n	'G', '  G',\n	'I', '  I', #In\
osine\n	);\n	\n	return %threelett;\n\n}\n\n\nsub f\
ill_onelett_RNA\n{\n	my   %onelett=(\n	'  A' => 'A\
',\n	'  T' => 'T',\n	'  U' => 'U',\n	'  C' => 'C',\
\n	'  G' => 'G',\n	'CSL' => 'X',\n	'UMS' => 'X',\n\
	'  I' => 'I',\n	'A' => 'A',\n	'T' => 'T',\n	'U' =\
> 'U',\n	'C' => 'C',\n	'G' => 'G',\n	'I' => 'I',\n\
	);\n\n	return %onelett;\n\n}\n\n\nsub fill_onelet\
t_DNA\n{\n	my   %onelett=(\n	' DA', 'A',\n	' DT', \
'T',\n	' DC', 'C',\n	' DG', 'G',\n	'DA', 'A',\n	'D\
T', 'T',\n	'DC', 'C',\n	'DG', 'G',\n	);\n\n	return\
 %onelett;\n\n}\n\nsub fill_threelett_DNA\n{\n\n	m\
y %threelett=(\n	'A', ' DA',\n	'T', ' DT',\n	'C', \
' DC',\n	'G', ' DG',\n	);\n\n	return %threelett;\n\
\n}\n\n\n\n\nsub fill_threelett_prot\n{  \n  my %t\
hreelett;\n\n  %threelett=(\n'A', 'ALA',\n'C', 'CY\
S',\n'D', 'ASP',\n'E', 'GLU',\n'F', 'PHE',\n'G', '\
GLY',\n'H', 'HIS',\n'I', 'ILE',\n'K', 'LYS',\n'L',\
 'LEU',\n'N', 'ASN',\n'M', 'MET',\n'P', 'PRO',\n'Q\
', 'GLN',\n'R', 'ARG',\n'S', 'SER',\n'T', 'THR',\n\
'V', 'VAL',\n'W', 'TRP',\n'Y', 'TYR',\n);\n\nretur\
n %threelett;\n\n\n}\n\nsub fill_onelett_prot\n{\n\
    my %onelett;\n    \n    %onelett=(\n\n'10A', '\
X',\n'11O', 'X',\n'12A', 'X',\n'13P', 'X',\n'13R',\
 'X',\n'13S', 'X',\n'14W', 'X',\n'15P', 'X',\n'16A\
', 'X',\n'16G', 'X',\n'1AN', 'X',\n'1AP', 'X',\n'1\
AR', 'X',\n'1BH', 'X',\n'1BO', 'X',\n'1C5', 'X',\n\
'1CU', 'X',\n'1DA', 'X',\n'1GL', 'X',\n'1GN', 'X',\
\n'1IN', 'X',\n'1LU', 'L',\n'1MA', 'X',\n'1MC', 'X\
',\n'1MG', 'X',\n'1MZ', 'X',\n'1NA', 'X',\n'1NB', \
'X',\n'1NI', 'X',\n'1PA', 'A',\n'1PC', 'X',\n'1PE'\
, 'X',\n'1PG', 'X',\n'1PI', 'A',\n'1PM', 'X',\n'1P\
N', 'X',\n'1PU', 'X',\n'1PY', 'X',\n'1UN', 'X',\n'\
24T', 'X',\n'25T', 'X',\n'26P', 'X',\n'2AB', 'X',\\
n'2AM', 'X',\n'2AN', 'X',\n'2AP', 'X',\n'2AR', 'X'\
,\n'2AS', 'D',\n'2BL', 'X',\n'2BM', 'X',\n'2CP', '\
X',\n'2DA', 'X',\n'2DG', 'X',\n'2DP', 'X',\n'2DT',\
 'X',\n'2EP', 'X',\n'2EZ', 'X',\n'2FG', 'X',\n'2FL\
', 'X',\n'2FP', 'X',\n'2FU', 'X',\n'2GL', 'X',\n'2\
GP', 'X',\n'2HP', 'X',\n'2IB', 'X',\n'2IP', 'X',\n\
'2LU', 'L',\n'2MA', 'X',\n'2MD', 'X',\n'2ME', 'X',\
\n'2MG', 'X',\n'2ML', 'L',\n'2MO', 'X',\n'2MR', 'R\
',\n'2MU', 'X',\n'2MZ', 'X',\n'2NO', 'X',\n'2NP', \
'X',\n'2OG', 'X',\n'2PA', 'X',\n'2PC', 'X',\n'2PE'\
, 'X',\n'2PG', 'X',\n'2PH', 'X',\n'2PI', 'X',\n'2P\
L', 'X',\n'2PP', 'X',\n'2PU', 'X',\n'2SI', 'X',\n'\
2TB', 'X',\n'34C', 'X',\n'35G', 'X',\n'3AA', 'X',\\
n'3AD', 'X',\n'3AH', 'H',\n'3AN', 'X',\n'3AP', 'X'\
,\n'3AT', 'X',\n'3BT', 'X',\n'3CH', 'X',\n'3CN', '\
X',\n'3CO', 'X',\n'3CP', 'X',\n'3DR', 'X',\n'3EP',\
 'X',\n'3FM', 'X',\n'3GA', 'X',\n'3GP', 'X',\n'3HB\
', 'X',\n'3HC', 'X',\n'3HP', 'X',\n'3IB', 'X',\n'3\
ID', 'X',\n'3IN', 'X',\n'3MA', 'X',\n'3MB', 'X',\n\
'3MC', 'X',\n'3MD', 'D',\n'3MF', 'X',\n'3MP', 'X',\
\n'3MT', 'X',\n'3OL', 'X',\n'3PA', 'X',\n'3PG', 'X\
',\n'3PO', 'X',\n'3PP', 'X',\n'3PY', 'X',\n'49A', \
'X',\n'4AB', 'X',\n'4AM', 'X',\n'4AN', 'X',\n'4AP'\
, 'X',\n'4BA', 'X',\n'4BT', 'X',\n'4CA', 'X',\n'4C\
O', 'X',\n'4HP', 'X',\n'4IP', 'X',\n'4MO', 'X',\n'\
4MV', 'X',\n'4MZ', 'X',\n'4NC', 'X',\n'4NP', 'X',\\
n'4OX', 'X',\n'4PB', 'X',\n'4PN', 'X',\n'4PP', 'X'\
,\n'4SC', 'X',\n'4SU', 'X',\n'4TB', 'X',\n'55C', '\
X',\n'5AD', 'X',\n'5AN', 'X',\n'5AT', 'X',\n'5CM',\
 'X',\n'5GP', 'X',\n'5HP', 'E',\n'5HT', 'X',\n'5IT\
', 'X',\n'5IU', 'X',\n'5MB', 'X',\n'5MC', 'X',\n'5\
MD', 'X',\n'5MP', 'X',\n'5MU', 'X',\n'5NC', 'X',\n\
'5OB', 'X',\n'5PA', 'X',\n'5PV', 'X',\n'6AB', 'X',\
\n'6CT', 'X',\n'6HA', 'X',\n'6HC', 'X',\n'6HG', 'X\
',\n'6HT', 'X',\n'6IN', 'X',\n'6MO', 'X',\n'6MP', \
'X',\n'6PG', 'X',\n'6WO', 'X',\n'70U', 'X',\n'7DG'\
, 'X',\n'7HP', 'X',\n'7I2', 'X',\n'7MG', 'X',\n'7M\
Q', 'X',\n'7NI', 'X',\n'87Y', 'X',\n'8AD', 'X',\n'\
8BR', 'X',\n'8IG', 'X',\n'8IN', 'X',\n'8OG', 'X',\\
n'95A', 'X',\n'9AD', 'X',\n'9AM', 'X',\n'9AP', 'X'\
,\n'9DG', 'X',\n'9DI', 'X',\n'9HX', 'X',\n'9OH', '\
X',\n'9TA', 'X',\n'A12', 'X',\n'A15', 'X',\n'A23',\
 'X',\n'A24', 'X',\n'A26', 'X',\n'A2G', 'X',\n'A2P\
', 'X',\n'A32', 'X',\n'A3P', 'X',\n'A4P', 'X',\n'A\
5P', 'X',\n'A70', 'X',\n'A76', 'X',\n'A77', 'X',\n\
'A78', 'X',\n'A79', 'X',\n'A80', 'X',\n'A85', 'X',\
\n'A88', 'X',\n'A9A', 'X',\n'AA3', 'X',\n'AA4', 'X\
',\n'AA6', 'X',\n'AAA', 'X',\n'AAB', 'X',\n'AAC', \
'X',\n'AAE', 'X',\n'AAG', 'R',\n'AAH', 'X',\n'AAM'\
, 'X',\n'AAN', 'X',\n'AAP', 'X',\n'AAR', 'R',\n'AA\
S', 'X',\n'AAT', 'X',\n'ABA', 'X',\n'ABC', 'X',\n'\
ABD', 'X',\n'ABE', 'X',\n'ABH', 'X',\n'ABI', 'X',\\
n'ABK', 'X',\n'ABM', 'X',\n'ABN', 'X',\n'ABP', 'X'\
,\n'ABR', 'X',\n'ABS', 'X',\n'ABU', 'X',\n'AC1', '\
X',\n'AC2', 'X',\n'ACA', 'X',\n'ACB', 'D',\n'ACC',\
 'C',\n'ACD', 'X',\n'ACE', 'X',\n'ACH', 'X',\n'ACI\
', 'X',\n'ACL', 'R',\n'ACM', 'X',\n'ACN', 'X',\n'A\
CO', 'X',\n'ACP', 'X',\n'ACQ', 'X',\n'ACR', 'X',\n\
'ACS', 'X',\n'ACT', 'X',\n'ACV', 'V',\n'ACX', 'X',\
\n'ACY', 'X',\n'AD2', 'X',\n'AD3', 'X',\n'ADC', 'X\
',\n'ADD', 'X',\n'ADE', 'X',\n'ADH', 'X',\n'ADI', \
'X',\n'ADM', 'X',\n'ADN', 'X',\n'ADP', 'X',\n'ADQ'\
, 'X',\n'ADR', 'X',\n'ADS', 'X',\n'ADT', 'X',\n'AD\
U', 'X',\n'ADW', 'X',\n'ADX', 'X',\n'AE2', 'X',\n'\
AEA', 'X',\n'AEB', 'X',\n'AEI', 'D',\n'AEN', 'X',\\
n'AET', 'T',\n'AF1', 'X',\n'AF3', 'X',\n'AFA', 'D'\
,\n'AFP', 'X',\n'AG7', 'X',\n'AGB', 'X',\n'AGF', '\
X',\n'AGL', 'X',\n'AGM', 'R',\n'AGN', 'X',\n'AGP',\
 'X',\n'AGS', 'X',\n'AGU', 'X',\n'AH0', 'X',\n'AH1\
', 'X',\n'AHA', 'X',\n'AHB', 'D',\n'AHC', 'X',\n'A\
HF', 'X',\n'AHG', 'X',\n'AHH', 'X',\n'AHM', 'X',\n\
'AHO', 'X',\n'AHP', 'X',\n'AHS', 'X',\n'AHT', 'Y',\
\n'AHU', 'X',\n'AHX', 'X',\n'AI1', 'X',\n'AI2', 'X\
',\n'AIB', 'X',\n'AIC', 'X',\n'AIM', 'X',\n'AIP', \
'X',\n'AIQ', 'X',\n'AIR', 'X',\n'AJ3', 'X',\n'AKB'\
, 'X',\n'AKG', 'X',\n'AKR', 'X',\n'AL1', 'X',\n'AL\
2', 'X',\n'AL3', 'X',\n'AL4', 'X',\n'AL5', 'X',\n'\
AL6', 'X',\n'AL7', 'X',\n'AL8', 'X',\n'AL9', 'X',\\
n'ALA', 'A',\n'ALB', 'X',\n'ALC', 'X',\n'ALD', 'L'\
,\n'ALE', 'X',\n'ALF', 'X',\n'ALG', 'X',\n'ALL', '\
X',\n'ALM', 'A',\n'ALN', 'A',\n'ALO', 'T',\n'ALP',\
 'X',\n'ALQ', 'X',\n'ALR', 'X',\n'ALS', 'X',\n'ALT\
', 'A',\n'ALY', 'K',\n'ALZ', 'X',\n'AMA', 'X',\n'A\
MB', 'X',\n'AMC', 'X',\n'AMD', 'X',\n'AMG', 'X',\n\
'AMH', 'X',\n'AMI', 'X',\n'AML', 'X',\n'AMN', 'X',\
\n'AMO', 'X',\n'AMP', 'X',\n'AMQ', 'X',\n'AMR', 'X\
',\n'AMS', 'X',\n'AMT', 'X',\n'AMU', 'X',\n'AMW', \
'X',\n'AMX', 'X',\n'AMY', 'X',\n'ANA', 'X',\n'ANB'\
, 'X',\n'ANC', 'X',\n'AND', 'X',\n'ANE', 'X',\n'AN\
I', 'X',\n'ANL', 'X',\n'ANO', 'X',\n'ANP', 'X',\n'\
ANS', 'X',\n'ANT', 'X',\n'AOE', 'X',\n'AOP', 'X',\\
n'AP1', 'X',\n'AP2', 'X',\n'AP3', 'X',\n'AP4', 'X'\
,\n'AP5', 'X',\n'AP6', 'X',\n'APA', 'X',\n'APB', '\
X',\n'APC', 'X',\n'APE', 'F',\n'APF', 'X',\n'APG',\
 'X',\n'APH', 'A',\n'API', 'X',\n'APL', 'X',\n'APM\
', 'X',\n'APN', 'G',\n'APP', 'X',\n'APQ', 'X',\n'A\
PR', 'X',\n'APS', 'X',\n'APT', 'X',\n'APU', 'X',\n\
'APX', 'X',\n'APY', 'X',\n'APZ', 'X',\n'AQS', 'X',\
\n'AR1', 'X',\n'AR2', 'X',\n'ARA', 'X',\n'ARB', 'X\
',\n'ARC', 'X',\n'ARD', 'X',\n'ARG', 'R',\n'ARH', \
'X',\n'ARI', 'X',\n'ARM', 'R',\n'ARN', 'X',\n'ARO'\
, 'R',\n'ARP', 'X',\n'ARQ', 'X',\n'ARS', 'X',\n'AS\
1', 'R',\n'AS2', 'X',\n'ASA', 'D',\n'ASB', 'D',\n'\
ASC', 'X',\n'ASD', 'X',\n'ASE', 'X',\n'ASF', 'X',\\
n'ASI', 'X',\n'ASK', 'D',\n'ASL', 'X',\n'ASM', 'N'\
,\n'ASO', 'X',\n'ASP', 'D',\n'ASQ', 'X',\n'ASU', '\
X',\n'ATA', 'X',\n'ATC', 'X',\n'ATD', 'X',\n'ATF',\
 'X',\n'ATG', 'X',\n'ATH', 'X',\n'ATM', 'X',\n'ATO\
', 'X',\n'ATP', 'X',\n'ATQ', 'X',\n'ATR', 'X',\n'A\
TT', 'X',\n'ATY', 'X',\n'ATZ', 'X',\n'AUC', 'X',\n\
'AUR', 'X',\n'AVG', 'X',\n'AXP', 'X',\n'AYA', 'A',\
\n'AZ2', 'X',\n'AZA', 'X',\n'AZC', 'X',\n'AZD', 'X\
',\n'AZE', 'X',\n'AZI', 'X',\n'AZL', 'X',\n'AZM', \
'X',\n'AZR', 'X',\n'AZT', 'X',\n'B12', 'X',\n'B1F'\
, 'F',\n'B2A', 'A',\n'B2F', 'F',\n'B2I', 'I',\n'B2\
V', 'V',\n'B3I', 'X',\n'B3P', 'X',\n'B7G', 'X',\n'\
B96', 'X',\n'B9A', 'X',\n'BA1', 'X',\n'BAA', 'X',\\
n'BAB', 'X',\n'BAC', 'X',\n'BAF', 'X',\n'BAH', 'X'\
,\n'BAI', 'X',\n'BAK', 'X',\n'BAL', 'A',\n'BAM', '\
X',\n'BAO', 'X',\n'BAP', 'X',\n'BAR', 'X',\n'BAS',\
 'X',\n'BAT', 'F',\n'BAY', 'X',\n'BAZ', 'X',\n'BB1\
', 'X',\n'BB2', 'X',\n'BBA', 'X',\n'BBH', 'X',\n'B\
BS', 'X',\n'BBT', 'X',\n'BBZ', 'X',\n'BCA', 'X',\n\
'BCB', 'X',\n'BCC', 'X',\n'BCD', 'X',\n'BCL', 'X',\
\n'BCN', 'X',\n'BCR', 'X',\n'BCS', 'C',\n'BCT', 'X\
',\n'BCY', 'X',\n'BCZ', 'X',\n'BDA', 'X',\n'BDG', \
'X',\n'BDK', 'X',\n'BDM', 'X',\n'BDN', 'X',\n'BDS'\
, 'X',\n'BE1', 'X',\n'BE2', 'X',\n'BEA', 'X',\n'BE\
F', 'X',\n'BEN', 'X',\n'BEO', 'X',\n'BEP', 'X',\n'\
BER', 'X',\n'BES', 'X',\n'BET', 'X',\n'BEZ', 'X',\\
n'BF2', 'X',\n'BFA', 'X',\n'BFD', 'X',\n'BFP', 'X'\
,\n'BFS', 'X',\n'BFU', 'X',\n'BG6', 'X',\n'BGF', '\
X',\n'BGG', 'X',\n'BGL', 'X',\n'BGN', 'X',\n'BGP',\
 'X',\n'BGX', 'X',\n'BH4', 'X',\n'BHA', 'X',\n'BHC\
', 'X',\n'BHD', 'D',\n'BHO', 'X',\n'BHS', 'X',\n'B\
IC', 'X',\n'BIN', 'X',\n'BIO', 'X',\n'BIP', 'X',\n\
'BIS', 'X',\n'BIZ', 'X',\n'BJH', 'X',\n'BJI', 'X',\
\n'BJP', 'X',\n'BLA', 'X',\n'BLB', 'X',\n'BLE', 'L\
',\n'BLG', 'P',\n'BLI', 'X',\n'BLM', 'X',\n'BLV', \
'X',\n'BLY', 'K',\n'BM1', 'X',\n'BM2', 'X',\n'BM5'\
, 'X',\n'BM9', 'X',\n'BMA', 'X',\n'BMD', 'X',\n'BM\
E', 'X',\n'BMP', 'X',\n'BMQ', 'X',\n'BMS', 'X',\n'\
BMT', 'T',\n'BMU', 'X',\n'BMY', 'X',\n'BMZ', 'X',\\
n'BNA', 'X',\n'BNG', 'X',\n'BNI', 'X',\n'BNN', 'F'\
,\n'BNO', 'L',\n'BNS', 'X',\n'BNZ', 'X',\n'BO3', '\
X',\n'BO4', 'X',\n'BOC', 'X',\n'BOG', 'X',\n'BOM',\
 'X',\n'BOT', 'X',\n'BOX', 'X',\n'BOZ', 'X',\n'BPA\
', 'X',\n'BPB', 'X',\n'BPD', 'X',\n'BPG', 'X',\n'B\
PH', 'X',\n'BPI', 'X',\n'BPJ', 'X',\n'BPM', 'X',\n\
'BPN', 'X',\n'BPO', 'X',\n'BPP', 'X',\n'BPT', 'X',\
\n'BPY', 'X',\n'BRB', 'X',\n'BRC', 'X',\n'BRE', 'X\
',\n'BRI', 'X',\n'BRL', 'X',\n'BRM', 'X',\n'BRN', \
'X',\n'BRO', 'X',\n'BRS', 'X',\n'BRU', 'X',\n'BRZ'\
, 'X',\n'BSB', 'X',\n'BSI', 'X',\n'BSP', 'X',\n'BT\
1', 'X',\n'BT2', 'X',\n'BT3', 'X',\n'BTA', 'L',\n'\
BTB', 'X',\n'BTC', 'C',\n'BTD', 'X',\n'BTN', 'X',\\
n'BTP', 'X',\n'BTR', 'W',\n'BU1', 'X',\n'BUA', 'X'\
,\n'BUB', 'X',\n'BUC', 'X',\n'BUG', 'X',\n'BUL', '\
X',\n'BUM', 'X',\n'BUQ', 'X',\n'BUT', 'X',\n'BVD',\
 'X',\n'BX3', 'X',\n'BYS', 'X',\n'BZ1', 'X',\n'BZA\
', 'X',\n'BZB', 'X',\n'BZC', 'X',\n'BZD', 'X',\n'B\
ZF', 'X',\n'BZI', 'X',\n'BZM', 'X',\n'BZO', 'X',\n\
'BZP', 'X',\n'BZQ', 'X',\n'BZS', 'X',\n'BZT', 'X',\
\n'C02', 'X',\n'C11', 'X',\n'C1O', 'X',\n'C20', 'X\
',\n'C24', 'X',\n'C2F', 'X',\n'C2O', 'X',\n'C2P', \
'X',\n'C3M', 'X',\n'C3P', 'X',\n'C3X', 'X',\n'C48'\
, 'X',\n'C4M', 'X',\n'C4X', 'X',\n'C5C', 'X',\n'C5\
M', 'X',\n'C5P', 'X',\n'C5X', 'X',\n'C60', 'X',\n'\
C6C', 'X',\n'C6M', 'X',\n'C78', 'X',\n'C8E', 'X',\\
n'CA3', 'X',\n'CA5', 'X',\n'CAA', 'X',\n'CAB', 'X'\
,\n'CAC', 'X',\n'CAD', 'X',\n'CAF', 'C',\n'CAG', '\
X',\n'CAH', 'X',\n'CAL', 'X',\n'CAM', 'X',\n'CAN',\
 'X',\n'CAO', 'X',\n'CAP', 'X',\n'CAQ', 'X',\n'CAR\
', 'X',\n'CAS', 'C',\n'CAT', 'X',\n'CAV', 'X',\n'C\
AY', 'C',\n'CAZ', 'X',\n'CB3', 'X',\n'CB4', 'X',\n\
'CBA', 'X',\n'CBD', 'X',\n'CBG', 'X',\n'CBI', 'X',\
\n'CBL', 'X',\n'CBM', 'X',\n'CBN', 'X',\n'CBO', 'X\
',\n'CBP', 'X',\n'CBS', 'X',\n'CBX', 'X',\n'CBZ', \
'X',\n'CC0', 'X',\n'CC1', 'X',\n'CCC', 'X',\n'CCH'\
, 'X',\n'CCI', 'X',\n'CCM', 'X',\n'CCN', 'X',\n'CC\
O', 'X',\n'CCP', 'X',\n'CCR', 'X',\n'CCS', 'C',\n'\
CCV', 'X',\n'CCY', 'X',\n'CD1', 'X',\n'CDC', 'X',\\
n'CDE', 'X',\n'CDF', 'X',\n'CDI', 'X',\n'CDL', 'X'\
,\n'CDM', 'X',\n'CDP', 'X',\n'CDR', 'X',\n'CDU', '\
X',\n'CE1', 'X',\n'CEA', 'C',\n'CEB', 'X',\n'CEC',\
 'X',\n'CED', 'X',\n'CEF', 'X',\n'CEH', 'X',\n'CEM\
', 'X',\n'CEO', 'X',\n'CEP', 'X',\n'CEQ', 'X',\n'C\
ER', 'X',\n'CES', 'G',\n'CET', 'X',\n'CFC', 'X',\n\
'CFF', 'X',\n'CFM', 'X',\n'CFO', 'X',\n'CFP', 'X',\
\n'CFS', 'X',\n'CFX', 'X',\n'CGN', 'X',\n'CGP', 'X\
',\n'CGS', 'X',\n'CGU', 'E',\n'CH2', 'X',\n'CH3', \
'X',\n'CHA', 'X',\n'CHB', 'X',\n'CHD', 'X',\n'CHF'\
, 'X',\n'CHG', 'G',\n'CHI', 'X',\n'CHN', 'X',\n'CH\
O', 'X',\n'CHP', 'G',\n'CHR', 'X',\n'CHS', 'F',\n'\
CHT', 'X',\n'CHX', 'X',\n'CIC', 'X',\n'CIN', 'X',\\
n'CIP', 'X',\n'CIR', 'X',\n'CIT', 'X',\n'CIU', 'X'\
,\n'CKI', 'X',\n'CL1', 'X',\n'CL2', 'X',\n'CLA', '\
X',\n'CLB', 'A',\n'CLC', 'S',\n'CLD', 'A',\n'CLE',\
 'L',\n'CLF', 'X',\n'CLK', 'S',\n'CLL', 'X',\n'CLM\
', 'X',\n'CLN', 'X',\n'CLO', 'X',\n'CLP', 'X',\n'C\
LQ', 'X',\n'CLR', 'X',\n'CLS', 'X',\n'CLT', 'X',\n\
'CLX', 'X',\n'CLY', 'X',\n'CMA', 'R',\n'CMC', 'X',\
\n'CMD', 'X',\n'CME', 'C',\n'CMG', 'X',\n'CMK', 'X\
',\n'CMN', 'X',\n'CMO', 'X',\n'CMP', 'X',\n'CMR', \
'X',\n'CMS', 'X',\n'CMT', 'C',\n'CMX', 'X',\n'CNA'\
, 'X',\n'CNC', 'X',\n'CND', 'X',\n'CNH', 'X',\n'CN\
M', 'X',\n'CNN', 'X',\n'CNO', 'X',\n'CNP', 'X',\n'\
CO2', 'X',\n'CO3', 'X',\n'CO5', 'X',\n'CO8', 'X',\\
n'COA', 'X',\n'COB', 'X',\n'COC', 'X',\n'COD', 'X'\
,\n'COE', 'X',\n'COF', 'X',\n'COH', 'X',\n'COI', '\
X',\n'COJ', 'X',\n'COL', 'X',\n'COM', 'X',\n'CON',\
 'X',\n'COP', 'X',\n'COR', 'X',\n'COS', 'X',\n'COT\
', 'X',\n'COY', 'X',\n'CP1', 'G',\n'CP2', 'X',\n'C\
P4', 'X',\n'CPA', 'X',\n'CPB', 'X',\n'CPC', 'X',\n\
'CPD', 'X',\n'CPG', 'X',\n'CPH', 'X',\n'CPI', 'X',\
\n'CPM', 'X',\n'CPN', 'G',\n'CPO', 'X',\n'CPP', 'X\
',\n'CPQ', 'X',\n'CPR', 'X',\n'CPS', 'X',\n'CPT', \
'X',\n'CPU', 'X',\n'CPV', 'X',\n'CPY', 'X',\n'CR1'\
, 'X',\n'CR6', 'X',\n'CRA', 'X',\n'CRB', 'X',\n'CR\
C', 'X',\n'CRG', 'X',\n'CRH', 'X',\n'CRO', 'T',\n'\
CRP', 'X',\n'CRQ', 'X',\n'CRS', 'X',\n'CRT', 'X',\\
n'CRY', 'X',\n'CSA', 'C',\n'CSB', 'X',\n'CSD', 'C'\
,\n'CSE', 'C',\n'CSH', 'X',\n'CSI', 'X',\n'CSN', '\
X',\n'CSO', 'C',\n'CSP', 'C',\n'CSR', 'C',\n'CSS',\
 'C',\n'CST', 'X',\n'CSW', 'C',\n'CSX', 'C',\n'CSY\
', 'X',\n'CSZ', 'C',\n'CT3', 'X',\n'CTA', 'X',\n'C\
TB', 'X',\n'CTC', 'X',\n'CTD', 'X',\n'CTH', 'T',\n\
'CTO', 'X',\n'CTP', 'X',\n'CTR', 'X',\n'CTS', 'X',\
\n'CTT', 'X',\n'CTY', 'X',\n'CTZ', 'X',\n'CU1', 'X\
',\n'CUA', 'X',\n'CUC', 'X',\n'CUL', 'X',\n'CUO', \
'X',\n'CUZ', 'X',\n'CVI', 'X',\n'CXF', 'X',\n'CXL'\
, 'X',\n'CXM', 'M',\n'CXN', 'X',\n'CXP', 'X',\n'CX\
S', 'X',\n'CY1', 'C',\n'CY3', 'X',\n'CYB', 'X',\n'\
CYC', 'X',\n'CYF', 'C',\n'CYG', 'C',\n'CYH', 'X',\\
n'CYL', 'X',\n'CYM', 'C',\n'CYN', 'X',\n'CYO', 'X'\
,\n'CYP', 'X',\n'CYQ', 'C',\n'CYS', 'C',\n'CYU', '\
X',\n'CYY', 'X',\n'CYZ', 'X',\n'CZH', 'X',\n'CZZ',\
 'C',\n'D12', 'X',\n'D13', 'X',\n'D16', 'X',\n'D18\
', 'X',\n'D19', 'X',\n'D1P', 'X',\n'D24', 'X',\n'D\
34', 'X',\n'D35', 'X',\n'D4D', 'X',\n'D4T', 'X',\n\
'D6G', 'X',\n'DA2', 'R',\n'DA3', 'X',\n'DA6', 'X',\
\n'DA7', 'X',\n'DAA', 'X',\n'DAB', 'X',\n'DAC', 'X\
',\n'DAD', 'X',\n'DAE', 'X',\n'DAF', 'X',\n'DAG', \
'X',\n'DAH', 'A',\n'DAJ', 'X',\n'DAK', 'X',\n'DAL'\
, 'A',\n'DAM', 'A',\n'DAN', 'X',\n'DAO', 'X',\n'DA\
P', 'X',\n'DAQ', 'X',\n'DAR', 'R',\n'DAS', 'D',\n'\
DAT', 'X',\n'DAU', 'X',\n'DAV', 'X',\n'DBA', 'X',\\
n'DBD', 'X',\n'DBF', 'X',\n'DBG', 'X',\n'DBI', 'X'\
,\n'DBV', 'X',\n'DBY', 'Y',\n'DCA', 'X',\n'DCB', '\
X',\n'DCE', 'X',\n'DCF', 'X',\n'DCG', 'X',\n'DCH',\
 'X',\n'DCI', 'I',\n'DCL', 'X',\n'DCM', 'X',\n'DCP\
', 'X',\n'DCS', 'X',\n'DCT', 'X',\n'DCY', 'C',\n'D\
CZ', 'X',\n'DDA', 'X',\n'DDB', 'X',\n'DDC', 'X',\n\
'DDF', 'X',\n'DDG', 'X',\n'DDH', 'X',\n'DDL', 'X',\
\n'DDM', 'X',\n'DDO', 'L',\n'DDP', 'X',\n'DDQ', 'X\
',\n'DDT', 'Y',\n'DDU', 'X',\n'DEA', 'X',\n'DEB', \
'X',\n'DEC', 'X',\n'DEF', 'X',\n'DEL', 'X',\n'DEM'\
, 'X',\n'DEN', 'X',\n'DEP', 'X',\n'DEQ', 'X',\n'DE\
S', 'X',\n'DET', 'X',\n'DFC', 'X',\n'DFG', 'X',\n'\
DFI', 'X',\n'DFL', 'X',\n'DFO', 'X',\n'DFP', 'X',\\
n'DFR', 'X',\n'DFT', 'X',\n'DFV', 'X',\n'DFX', 'X'\
,\n'DG2', 'X',\n'DG3', 'X',\n'DG6', 'X',\n'DGA', '\
X',\n'DGD', 'X',\n'DGG', 'X',\n'DGL', 'E',\n'DGN',\
 'Q',\n'DGP', 'X',\n'DGT', 'X',\n'DGX', 'X',\n'DH2\
', 'X',\n'DHA', 'A',\n'DHB', 'X',\n'DHC', 'X',\n'D\
HD', 'X',\n'DHE', 'X',\n'DHF', 'X',\n'DHG', 'X',\n\
'DHI', 'H',\n'DHL', 'X',\n'DHM', 'X',\n'DHN', 'V',\
\n'DHP', 'X',\n'DHQ', 'X',\n'DHR', 'X',\n'DHS', 'X\
',\n'DHT', 'X',\n'DHU', 'X',\n'DHY', 'X',\n'DHZ', \
'X',\n'DI2', 'X',\n'DI3', 'G',\n'DI4', 'X',\n'DI5'\
, 'X',\n'DIA', 'X',\n'DIC', 'X',\n'DIF', 'X',\n'DI\
G', 'X',\n'DII', 'X',\n'DIL', 'I',\n'DIM', 'X',\n'\
DIO', 'X',\n'DIP', 'X',\n'DIQ', 'X',\n'DIS', 'X',\\
n'DIT', 'X',\n'DIV', 'V',\n'DIX', 'X',\n'DIY', 'X'\
,\n'DKA', 'X',\n'DLA', 'X',\n'DLE', 'L',\n'DLF', '\
X',\n'DLS', 'K',\n'DLY', 'K',\n'DM1', 'X',\n'DM2',\
 'X',\n'DM3', 'X',\n'DM4', 'X',\n'DM5', 'X',\n'DM6\
', 'X',\n'DM7', 'X',\n'DM8', 'X',\n'DM9', 'X',\n'D\
MA', 'X',\n'DMB', 'X',\n'DMC', 'X',\n'DMD', 'X',\n\
'DME', 'X',\n'DMF', 'X',\n'DMG', 'G',\n'DMH', 'N',\
\n'DMI', 'X',\n'DMJ', 'X',\n'DML', 'X',\n'DMM', 'X\
',\n'DMN', 'X',\n'DMO', 'X',\n'DMP', 'X',\n'DMQ', \
'X',\n'DMR', 'X',\n'DMS', 'X',\n'DMT', 'X',\n'DMV'\
, 'X',\n'DMY', 'X',\n'DNC', 'X',\n'DND', 'X',\n'DN\
H', 'X',\n'DNJ', 'X',\n'DNN', 'X',\n'DNP', 'X',\n'\
DNQ', 'X',\n'DNR', 'X',\n'DO2', 'X',\n'DO3', 'X',\\
n'DOA', 'X',\n'DOB', 'X',\n'DOC', 'X',\n'DOH', 'D'\
,\n'DOM', 'X',\n'DOS', 'X',\n'DOX', 'X',\n'DP5', '\
X',\n'DP7', 'X',\n'DPA', 'X',\n'DPC', 'X',\n'DPD',\
 'X',\n'DPE', 'X',\n'DPG', 'X',\n'DPH', 'F',\n'DPM\
', 'X',\n'DPN', 'F',\n'DPO', 'X',\n'DPP', 'X',\n'D\
PR', 'P',\n'DPS', 'X',\n'DPT', 'X',\n'DPX', 'X',\n\
'DPY', 'X',\n'DPZ', 'X',\n'DQH', 'X',\n'DQN', 'X',\
\n'DR1', 'X',\n'DRB', 'X',\n'DRC', 'X',\n'DRI', 'X\
',\n'DRP', 'X',\n'DRT', 'X',\n'DRU', 'X',\n'DSA', \
'X',\n'DSB', 'X',\n'DSC', 'X',\n'DSD', 'X',\n'DSE'\
, 'S',\n'DSI', 'X',\n'DSN', 'S',\n'DSP', 'D',\n'DS\
R', 'X',\n'DSS', 'X',\n'DSX', 'X',\n'DSY', 'X',\n'\
DTB', 'X',\n'DTD', 'X',\n'DTH', 'T',\n'DTN', 'X',\\
n'DTO', 'X',\n'DTP', 'X',\n'DTQ', 'X',\n'DTR', 'W'\
,\n'DTT', 'X',\n'DTY', 'Y',\n'DUD', 'X',\n'DUO', '\
X',\n'DUR', 'X',\n'DUT', 'X',\n'DVA', 'V',\n'DVR',\
 'X',\n'DX9', 'X',\n'DXA', 'X',\n'DXB', 'X',\n'DXC\
', 'X',\n'DXG', 'X',\n'DXX', 'X',\n'DZF', 'X',\n'E\
09', 'X',\n'E20', 'X',\n'E2P', 'X',\n'E3G', 'X',\n\
'E4N', 'X',\n'E4P', 'X',\n'E64', 'X',\n'E6C', 'X',\
\n'E96', 'X',\n'E97', 'X',\n'EA2', 'X',\n'EAA', 'X\
',\n'EAP', 'X',\n'EBP', 'X',\n'EBW', 'X',\n'ECO', \
'X',\n'EDA', 'X',\n'EDC', 'X',\n'EDE', 'X',\n'EDO'\
, 'X',\n'EDR', 'X',\n'EEB', 'X',\n'EEE', 'X',\n'EF\
C', 'X',\n'EFZ', 'X',\n'EG1', 'X',\n'EG2', 'X',\n'\
EG3', 'X',\n'EGC', 'X',\n'EGL', 'X',\n'EHP', 'A',\\
n'EIC', 'X',\n'EJT', 'X',\n'ELA', 'X',\n'EMB', 'X'\
,\n'EMC', 'X',\n'EMD', 'X',\n'EMM', 'X',\n'EMO', '\
X',\n'EMP', 'X',\n'EMR', 'X',\n'ENA', 'X',\n'ENC',\
 'X',\n'ENH', 'X',\n'ENO', 'X',\n'ENP', 'X',\n'EOA\
', 'X',\n'EOH', 'X',\n'EOT', 'X',\n'EOX', 'X',\n'E\
PA', 'X',\n'EPE', 'X',\n'EPH', 'X',\n'EPI', 'X',\n\
'EPN', 'X',\n'EPO', 'X',\n'EPT', 'X',\n'EPU', 'X',\
\n'EPX', 'X',\n'EPY', 'X',\n'EQI', 'X',\n'EQP', 'X\
',\n'EQU', 'X',\n'ERG', 'X',\n'ERI', 'X',\n'ERY', \
'X',\n'ESC', 'X',\n'ESD', 'X',\n'ESI', 'X',\n'ESO'\
, 'X',\n'ESP', 'X',\n'EST', 'X',\n'ESX', 'X',\n'ET\
A', 'X',\n'ETC', 'X',\n'ETD', 'X',\n'ETF', 'X',\n'\
ETH', 'X',\n'ETI', 'X',\n'ETN', 'X',\n'ETO', 'X',\\
n'ETP', 'X',\n'ETR', 'X',\n'ETS', 'X',\n'ETY', 'X'\
,\n'EU3', 'X',\n'EUG', 'X',\n'EYS', 'C',\n'F09', '\
X',\n'F2B', 'X',\n'F3S', 'X',\n'F42', 'X',\n'F43',\
 'X',\n'F4S', 'X',\n'F6B', 'X',\n'F6P', 'X',\n'F89\
', 'X',\n'FA1', 'X',\n'FA5', 'F',\n'FAA', 'X',\n'F\
AB', 'X',\n'FAC', 'X',\n'FAD', 'X',\n'FAF', 'X',\n\
'FAG', 'X',\n'FAM', 'X',\n'FAR', 'X',\n'FAS', 'X',\
\n'FAT', 'X',\n'FBA', 'X',\n'FBE', 'X',\n'FBI', 'X\
',\n'FBP', 'X',\n'FBQ', 'X',\n'FBS', 'X',\n'FBT', \
'X',\n'FBU', 'X',\n'FCA', 'X',\n'FCB', 'X',\n'FCI'\
, 'X',\n'FCN', 'X',\n'FCO', 'X',\n'FCR', 'X',\n'FC\
T', 'X',\n'FCX', 'X',\n'FCY', 'C',\n'FD1', 'F',\n'\
FD2', 'F',\n'FD3', 'F',\n'FD4', 'F',\n'FDA', 'X',\\
n'FDC', 'X',\n'FDI', 'X',\n'FDP', 'X',\n'FDS', 'X'\
,\n'FE2', 'X',\n'FEA', 'X',\n'FEL', 'X',\n'FEM', '\
X',\n'FEN', 'X',\n'FEO', 'X',\n'FEP', 'X',\n'FER',\
 'X',\n'FES', 'X',\n'FFB', 'X',\n'FFC', 'X',\n'FFF\
', 'X',\n'FFO', 'X',\n'FGL', 'G',\n'FHB', 'X',\n'F\
HC', 'X',\n'FHP', 'X',\n'FHU', 'X',\n'FID', 'X',\n\
'FII', 'X',\n'FIP', 'X',\n'FK5', 'X',\n'FKA', 'X',\
\n'FKI', 'X',\n'FKP', 'X',\n'FL2', 'X',\n'FL9', 'X\
',\n'FLA', 'A',\n'FLC', 'X',\n'FLD', 'X',\n'FLE', \
'L',\n'FLF', 'X',\n'FLO', 'X',\n'FLP', 'X',\n'FLT'\
, 'Y',\n'FLU', 'X',\n'FLX', 'X',\n'FM1', 'X',\n'FM\
2', 'X',\n'FMA', 'X',\n'FMB', 'X',\n'FMC', 'X',\n'\
FME', 'M',\n'FMN', 'X',\n'FMP', 'X',\n'FMR', 'X',\\
n'FMS', 'X',\n'FMT', 'X',\n'FNE', 'X',\n'FNP', 'X'\
,\n'FNS', 'X',\n'FOC', 'X',\n'FOE', 'X',\n'FOG', '\
F',\n'FOH', 'X',\n'FOK', 'X',\n'FOL', 'X',\n'FON',\
 'X',\n'FOP', 'X',\n'FOR', 'X',\n'FOS', 'X',\n'FPA\
', 'X',\n'FPC', 'X',\n'FPI', 'X',\n'FPO', 'X',\n'F\
PP', 'X',\n'FPT', 'X',\n'FQP', 'X',\n'FRA', 'X',\n\
'FRD', 'F',\n'FRU', 'X',\n'FS3', 'X',\n'FS4', 'X',\
\n'FSB', 'X',\n'FSO', 'X',\n'FSX', 'X',\n'FTC', 'X\
',\n'FTP', 'X',\n'FTR', 'W',\n'FTT', 'X',\n'FTY', \
'Y',\n'FUA', 'X',\n'FUC', 'X',\n'FUM', 'X',\n'FUP'\
, 'X',\n'FVF', 'X',\n'FXP', 'X',\n'FXV', 'X',\n'FY\
A', 'F',\n'G16', 'X',\n'G1P', 'X',\n'G20', 'X',\n'\
G21', 'X',\n'G23', 'X',\n'G26', 'X',\n'G28', 'X',\\
n'G2F', 'X',\n'G37', 'X',\n'G39', 'X',\n'G3H', 'X'\
,\n'G3P', 'X',\n'G4D', 'X',\n'G6D', 'X',\n'G6P', '\
X',\n'G6Q', 'X',\n'G7M', 'X',\n'GA2', 'X',\n'GAA',\
 'X',\n'GAB', 'X',\n'GAC', 'X',\n'GAI', 'X',\n'GAL\
', 'X',\n'GAM', 'X',\n'GAN', 'X',\n'GAO', 'X',\n'G\
AP', 'X',\n'GAR', 'G',\n'GAS', 'X',\n'GAT', 'X',\n\
'GBC', 'X',\n'GBI', 'X',\n'GBP', 'X',\n'GBS', 'X',\
\n'GBX', 'X',\n'GC4', 'X',\n'GCA', 'X',\n'GCD', 'X\
',\n'GCG', 'G',\n'GCH', 'G',\n'GCK', 'X',\n'GCL', \
'X',\n'GCM', 'X',\n'GCN', 'X',\n'GCO', 'X',\n'GCP'\
, 'X',\n'GCR', 'X',\n'GCS', 'X',\n'GCU', 'X',\n'GD\
3', 'X',\n'GDB', 'X',\n'GDM', 'X',\n'GDN', 'X',\n'\
GDP', 'X',\n'GDS', 'X',\n'GDU', 'X',\n'GE1', 'X',\\
n'GE2', 'X',\n'GE3', 'X',\n'GEA', 'X',\n'GEL', 'X'\
,\n'GEM', 'X',\n'GEN', 'X',\n'GEP', 'X',\n'GER', '\
X',\n'GFP', 'X',\n'GGB', 'X',\n'GGL', 'E',\n'GGP',\
 'X',\n'GHP', 'G',\n'GIP', 'X',\n'GIS', 'X',\n'GKR\
', 'X',\n'GL2', 'X',\n'GL3', 'G',\n'GL4', 'X',\n'G\
L5', 'X',\n'GL7', 'X',\n'GL9', 'X',\n'GLA', 'X',\n\
'GLB', 'X',\n'GLC', 'X',\n'GLD', 'X',\n'GLE', 'X',\
\n'GLF', 'X',\n'GLG', 'X',\n'GLH', 'Q',\n'GLI', 'X\
',\n'GLL', 'X',\n'GLM', 'G',\n'GLN', 'Q',\n'GLO', \
'X',\n'GLP', 'X',\n'GLR', 'X',\n'GLS', 'X',\n'GLT'\
, 'X',\n'GLU', 'E',\n'GLV', 'X',\n'GLW', 'X',\n'GL\
Y', 'G',\n'GLZ', 'X',\n'GM1', 'X',\n'GMA', 'X',\n'\
GMC', 'X',\n'GMH', 'X',\n'GMP', 'X',\n'GMY', 'X',\\
n'GN7', 'X',\n'GNA', 'X',\n'GNB', 'X',\n'GNH', 'X'\
,\n'GNP', 'X',\n'GNT', 'X',\n'GOA', 'X',\n'GOL', '\
X',\n'GOX', 'X',\n'GP1', 'X',\n'GP3', 'X',\n'GP4',\
 'X',\n'GP6', 'X',\n'GP8', 'X',\n'GPB', 'E',\n'GPC\
', 'X',\n'GPE', 'X',\n'GPG', 'X',\n'GPI', 'X',\n'G\
PJ', 'X',\n'GPL', 'K',\n'GPM', 'X',\n'GPN', 'G',\n\
'GPP', 'X',\n'GPR', 'X',\n'GPS', 'X',\n'GPX', 'X',\
\n'GR1', 'X',\n'GR3', 'X',\n'GR4', 'X',\n'GSA', 'X\
',\n'GSB', 'X',\n'GSC', 'G',\n'GSE', 'S',\n'GSH', \
'X',\n'GSP', 'X',\n'GSR', 'X',\n'GSS', 'X',\n'GT9'\
, 'C',\n'GTA', 'X',\n'GTB', 'X',\n'GTD', 'X',\n'GT\
E', 'X',\n'GTH', 'T',\n'GTN', 'X',\n'GTO', 'X',\n'\
GTP', 'X',\n'GTR', 'X',\n'GTS', 'X',\n'GTT', 'X',\\
n'GTX', 'X',\n'GTZ', 'X',\n'GU7', 'X',\n'GUA', 'X'\
,\n'GUD', 'X',\n'GUM', 'X',\n'GUN', 'X',\n'GUP', '\
X',\n'GUR', 'X',\n'GW3', 'X',\n'GZZ', 'X',\n'H2B',\
 'X',\n'H2P', 'H',\n'H2S', 'X',\n'H2U', 'X',\n'H4B\
', 'X',\n'H5M', 'P',\n'H5P', 'X',\n'HAA', 'X',\n'H\
AB', 'X',\n'HAC', 'A',\n'HAD', 'X',\n'HAE', 'X',\n\
'HAG', 'X',\n'HAI', 'X',\n'HAM', 'X',\n'HAP', 'X',\
\n'HAQ', 'X',\n'HAR', 'R',\n'HAS', 'X',\n'HAV', 'V\
',\n'HAX', 'X',\n'HAZ', 'X',\n'HBA', 'X',\n'HBC', \
'X',\n'HBD', 'X',\n'HBI', 'X',\n'HBO', 'X',\n'HBU'\
, 'X',\n'HBY', 'X',\n'HC0', 'X',\n'HC1', 'X',\n'HC\
4', 'X',\n'HCA', 'X',\n'HCC', 'X',\n'HCI', 'X',\n'\
HCS', 'X',\n'HDA', 'X',\n'HDD', 'X',\n'HDF', 'X',\\
n'HDN', 'X',\n'HDS', 'X',\n'HDZ', 'X',\n'HE1', 'X'\
,\n'HE6', 'X',\n'HEA', 'X',\n'HEB', 'X',\n'HEC', '\
X',\n'HED', 'X',\n'HEE', 'X',\n'HEF', 'X',\n'HEG',\
 'X',\n'HEM', 'X',\n'HEN', 'X',\n'HEO', 'X',\n'HEP\
', 'X',\n'HEU', 'X',\n'HEV', 'X',\n'HEX', 'X',\n'H\
EZ', 'X',\n'HF1', 'X',\n'HFA', 'X',\n'HFP', 'X',\n\
'HGA', 'Q',\n'HGB', 'X',\n'HGC', 'X',\n'HGI', 'X',\
\n'HGU', 'X',\n'HHO', 'X',\n'HHP', 'X',\n'HIB', 'X\
',\n'HIC', 'H',\n'HII', 'X',\n'HIN', 'X',\n'HIO', \
'X',\n'HIP', 'H',\n'HIS', 'H',\n'HLE', 'X',\n'HLT'\
, 'X',\n'HMA', 'A',\n'HMB', 'X',\n'HMC', 'X',\n'HM\
D', 'X',\n'HMF', 'A',\n'HMG', 'X',\n'HMH', 'X',\n'\
HMI', 'L',\n'HMM', 'X',\n'HMN', 'X',\n'HMO', 'X',\\
n'HMP', 'X',\n'HMR', 'R',\n'HNI', 'X',\n'HNP', 'X'\
,\n'HOA', 'X',\n'HOE', 'X',\n'HOH', 'X',\n'HOM', '\
X',\n'HOP', 'X',\n'HOQ', 'X',\n'HP1', 'A',\n'HP2',\
 'A',\n'HP3', 'X',\n'HPA', 'X',\n'HPB', 'X',\n'HPC\
', 'X',\n'HPD', 'X',\n'HPE', 'A',\n'HPG', 'X',\n'H\
PH', 'F',\n'HPP', 'X',\n'HPQ', 'F',\n'HPR', 'X',\n\
'HPT', 'X',\n'HPY', 'X',\n'HQO', 'X',\n'HQQ', 'X',\
\n'HQU', 'X',\n'HRG', 'R',\n'HRI', 'X',\n'HSA', 'X\
',\n'HSE', 'S',\n'HSF', 'X',\n'HSM', 'X',\n'HSO', \
'H',\n'HSP', 'X',\n'HT1', 'X',\n'HT2', 'X',\n'HTA'\
, 'X',\n'HTL', 'X',\n'HTO', 'X',\n'HTP', 'X',\n'HT\
R', 'W',\n'HUP', 'X',\n'HUX', 'X',\n'HV5', 'A',\n'\
HV7', 'X',\n'HV8', 'X',\n'HXA', 'X',\n'HXC', 'X',\\
n'HXP', 'X',\n'HY1', 'X',\n'HYA', 'X',\n'HYB', 'X'\
,\n'HYD', 'X',\n'HYG', 'X',\n'HYP', 'P',\n'I06', '\
X',\n'I10', 'X',\n'I11', 'X',\n'I17', 'X',\n'I2P',\
 'X',\n'I3N', 'X',\n'I3P', 'X',\n'I40', 'X',\n'I48\
', 'X',\n'I4B', 'X',\n'I52', 'X',\n'I5P', 'X',\n'I\
84', 'G',\n'IAG', 'G',\n'IAS', 'X',\n'IB2', 'X',\n\
'IBB', 'X',\n'IBP', 'X',\n'IBR', 'X',\n'IBS', 'X',\
\n'IBZ', 'X',\n'IC1', 'X',\n'ICA', 'X',\n'ICI', 'X\
',\n'ICL', 'X',\n'ICP', 'X',\n'ICT', 'X',\n'ICU', \
'X',\n'ID2', 'X',\n'IDC', 'X',\n'IDG', 'X',\n'IDH'\
, 'X',\n'IDM', 'X',\n'IDO', 'X',\n'IDP', 'X',\n'ID\
R', 'X',\n'IDS', 'X',\n'IDT', 'X',\n'IDU', 'X',\n'\
IFG', 'X',\n'IFP', 'X',\n'IGL', 'X',\n'IGN', 'X',\\
n'IGP', 'X',\n'IGU', 'X',\n'IH1', 'X',\n'IH2', 'X'\
,\n'IH3', 'X',\n'IHB', 'X',\n'IHN', 'X',\n'IHP', '\
X',\n'IIC', 'X',\n'IIL', 'I',\n'IIP', 'X',\n'IK2',\
 'X',\n'IKT', 'X',\n'ILA', 'I',\n'ILE', 'I',\n'ILG\
', 'X',\n'ILO', 'X',\n'ILX', 'I',\n'IM1', 'X',\n'I\
M2', 'X',\n'IMC', 'X',\n'IMD', 'X',\n'IME', 'X',\n\
'IMF', 'X',\n'IMG', 'X',\n'IMH', 'X',\n'IMI', 'X',\
\n'IML', 'I',\n'IMM', 'X',\n'IMN', 'X',\n'IMO', 'X\
',\n'IMP', 'X',\n'IMR', 'X',\n'IMU', 'X',\n'IN0', \
'D',\n'IN1', 'R',\n'IN2', 'K',\n'IN3', 'L',\n'IN4'\
, 'X',\n'IN5', 'A',\n'IN6', 'L',\n'IN7', 'X',\n'IN\
8', 'X',\n'IN9', 'X',\n'INA', 'L',\n'INB', 'X',\n'\
INC', 'X',\n'IND', 'X',\n'INE', 'X',\n'INF', 'F',\\
n'ING', 'F',\n'INH', 'R',\n'INI', 'X',\n'INJ', 'X'\
,\n'INK', 'X',\n'INL', 'X',\n'INM', 'X',\n'INN', '\
A',\n'INO', 'X',\n'INP', 'X',\n'INQ', 'X',\n'INR',\
 'X',\n'INS', 'X',\n'INT', 'V',\n'INU', 'X',\n'INV\
', 'X',\n'INW', 'X',\n'INX', 'X',\n'INY', 'X',\n'I\
NZ', 'X',\n'IOA', 'X',\n'IOB', 'X',\n'IOC', 'X',\n\
'IOD', 'X',\n'IOE', 'X',\n'IOF', 'X',\n'IOH', 'X',\
\n'IOL', 'X',\n'IOP', 'X',\n'IP1', 'X',\n'IP2', 'X\
',\n'IP3', 'X',\n'IP4', 'X',\n'IPA', 'X',\n'IPB', \
'X',\n'IPD', 'X',\n'IPG', 'G',\n'IPH', 'X',\n'IPL'\
, 'X',\n'IPM', 'X',\n'IPN', 'X',\n'IPO', 'F',\n'IP\
P', 'X',\n'IPS', 'X',\n'IPT', 'X',\n'IPU', 'X',\n'\
IPY', 'A',\n'IQB', 'X',\n'IQP', 'X',\n'IQS', 'X',\\
n'IR3', 'X',\n'IRI', 'X',\n'IRP', 'X',\n'ISA', 'X'\
,\n'ISF', 'X',\n'ISO', 'X',\n'ISP', 'X',\n'ISQ', '\
X',\n'ISU', 'X',\n'ITM', 'X',\n'ITP', 'X',\n'ITR',\
 'W',\n'ITS', 'X',\n'ITU', 'X',\n'IU5', 'X',\n'IUM\
', 'X',\n'IUR', 'X',\n'IVA', 'X',\n'IYG', 'G',\n'I\
YR', 'Y',\n'J77', 'X',\n'J78', 'X',\n'J80', 'X',\n\
'JE2', 'X',\n'JEN', 'X',\n'JST', 'X',\n'K21', 'X',\
\n'KAH', 'X',\n'KAI', 'X',\n'KAM', 'X',\n'KAN', 'X\
',\n'KAP', 'X',\n'KCP', 'X',\n'KCX', 'K',\n'KDO', \
'X',\n'KEF', 'X',\n'KET', 'X',\n'KGR', 'X',\n'KH1'\
, 'X',\n'KIF', 'X',\n'KIV', 'V',\n'KNI', 'X',\n'KP\
H', 'K',\n'KTH', 'X',\n'KTN', 'X',\n'KTP', 'X',\n'\
KWT', 'X',\n'L04', 'X',\n'L1P', 'X',\n'L24', 'E',\\
n'L2P', 'X',\n'L34', 'E',\n'L37', 'E',\n'L3P', 'X'\
,\n'L4P', 'X',\n'L75', 'X',\n'LAC', 'X',\n'LAD', '\
X',\n'LAK', 'X',\n'LAM', 'X',\n'LAR', 'X',\n'LAT',\
 'X',\n'LAX', 'X',\n'LCO', 'X',\n'LCP', 'X',\n'LCS\
', 'X',\n'LDA', 'X',\n'LDO', 'L',\n'LDP', 'X',\n'L\
EA', 'X',\n'LEO', 'X',\n'LEU', 'L',\n'LG2', 'X',\n\
'LG6', 'X',\n'LGC', 'X',\n'LGP', 'X',\n'LHG', 'X',\
\n'LHY', 'F',\n'LI1', 'X',\n'LIG', 'X',\n'LIL', 'X\
',\n'LIM', 'X',\n'LIN', 'X',\n'LIO', 'X',\n'LIP', \
'X',\n'LLA', 'X',\n'LLP', 'K',\n'LLY', 'K',\n'LMG'\
, 'X',\n'LML', 'X',\n'LMT', 'X',\n'LMU', 'X',\n'LM\
Z', 'X',\n'LNK', 'X',\n'LNL', 'X',\n'LNO', 'X',\n'\
LOF', 'X',\n'LOL', 'L',\n'LOM', 'X',\n'LOR', 'X',\\
n'LOS', 'X',\n'LOV', 'L',\n'LOX', 'X',\n'LP1', 'X'\
,\n'LP2', 'R',\n'LPA', 'X',\n'LPC', 'X',\n'LPF', '\
X',\n'LPL', 'X',\n'LPM', 'X',\n'LPP', 'X',\n'LRB',\
 'X',\n'LRU', 'X',\n'LS1', 'X',\n'LS2', 'X',\n'LS3\
', 'X',\n'LS4', 'X',\n'LS5', 'X',\n'LTA', 'X',\n'L\
TL', 'X',\n'LTR', 'W',\n'LUM', 'X',\n'LVS', 'L',\n\
'LXC', 'X',\n'LY2', 'X',\n'LY3', 'X',\n'LYA', 'X',\
\n'LYB', 'X',\n'LYC', 'X',\n'LYD', 'X',\n'LYM', 'K\
',\n'LYN', 'X',\n'LYS', 'K',\n'LYT', 'X',\n'LYW', \
'X',\n'LYZ', 'K',\n'M1A', 'X',\n'M1G', 'X',\n'M2G'\
, 'X',\n'M3L', 'K',\n'M6P', 'X',\n'M6T', 'X',\n'M7\
G', 'X',\n'MA1', 'X',\n'MA2', 'X',\n'MA3', 'X',\n'\
MA4', 'X',\n'MA6', 'X',\n'MAA', 'A',\n'MAB', 'X',\\
n'MAC', 'X',\n'MAE', 'X',\n'MAG', 'X',\n'MAH', 'X'\
,\n'MAI', 'R',\n'MAK', 'X',\n'MAL', 'X',\n'MAM', '\
X',\n'MAN', 'X',\n'MAO', 'X',\n'MAP', 'X',\n'MAR',\
 'X',\n'MAS', 'X',\n'MAT', 'X',\n'MAU', 'X',\n'MAZ\
', 'X',\n'MBA', 'X',\n'MBD', 'X',\n'MBG', 'X',\n'M\
BH', 'X',\n'MBN', 'X',\n'MBO', 'X',\n'MBR', 'X',\n\
'MBS', 'X',\n'MBV', 'X',\n'MBZ', 'X',\n'MCA', 'X',\
\n'MCD', 'X',\n'MCE', 'X',\n'MCG', 'G',\n'MCI', 'X\
',\n'MCN', 'X',\n'MCP', 'X',\n'MCT', 'X',\n'MCY', \
'X',\n'MD2', 'X',\n'MDA', 'X',\n'MDC', 'X',\n'MDG'\
, 'X',\n'MDH', 'X',\n'MDL', 'X',\n'MDM', 'X',\n'MD\
N', 'X',\n'MDP', 'X',\n'ME6', 'X',\n'MEB', 'X',\n'\
MEC', 'X',\n'MEL', 'X',\n'MEN', 'N',\n'MEP', 'X',\\
n'MER', 'X',\n'MES', 'X',\n'MET', 'M',\n'MEV', 'X'\
,\n'MF2', 'X',\n'MF3', 'M',\n'MFB', 'X',\n'MFD', '\
X',\n'MFU', 'X',\n'MG7', 'X',\n'MGA', 'X',\n'MGB',\
 'X',\n'MGD', 'X',\n'MGG', 'R',\n'MGL', 'X',\n'MGN\
', 'Q',\n'MGO', 'X',\n'MGP', 'X',\n'MGR', 'X',\n'M\
GS', 'X',\n'MGT', 'X',\n'MGU', 'X',\n'MGY', 'G',\n\
'MHB', 'X',\n'MHF', 'X',\n'MHL', 'L',\n'MHM', 'X',\
\n'MHO', 'M',\n'MHS', 'H',\n'MHZ', 'X',\n'MIA', 'X\
',\n'MIC', 'X',\n'MID', 'X',\n'MIL', 'X',\n'MIM', \
'X',\n'MIN', 'G',\n'MIP', 'X',\n'MIS', 'S',\n'MIT'\
, 'X',\n'MJI', 'X',\n'MK1', 'X',\n'MKC', 'X',\n'ML\
A', 'X',\n'MLC', 'X',\n'MLE', 'L',\n'MLN', 'X',\n'\
MLT', 'X',\n'MLY', 'K',\n'MLZ', 'K',\n'MM3', 'X',\\
n'MM4', 'X',\n'MMA', 'X',\n'MMC', 'X',\n'MME', 'M'\
,\n'MMO', 'R',\n'MMP', 'X',\n'MMQ', 'X',\n'MMT', '\
X',\n'MN1', 'X',\n'MN2', 'X',\n'MN3', 'X',\n'MN5',\
 'X',\n'MN7', 'X',\n'MN8', 'X',\n'MNA', 'X',\n'MNB\
', 'X',\n'MNC', 'X',\n'MNG', 'X',\n'MNL', 'L',\n'M\
NO', 'X',\n'MNP', 'X',\n'MNQ', 'X',\n'MNS', 'X',\n\
'MNT', 'X',\n'MNV', 'V',\n'MO1', 'X',\n'MO2', 'X',\
\n'MO3', 'X',\n'MO4', 'X',\n'MO5', 'X',\n'MO6', 'X\
',\n'MOA', 'X',\n'MOB', 'X',\n'MOC', 'X',\n'MOE', \
'X',\n'MOG', 'X',\n'MOH', 'X',\n'MOL', 'X',\n'MOO'\
, 'X',\n'MOP', 'X',\n'MOR', 'X',\n'MOS', 'X',\n'MO\
T', 'X',\n'MOX', 'X',\n'MP1', 'X',\n'MP3', 'X',\n'\
MPA', 'X',\n'MPB', 'X',\n'MPC', 'X',\n'MPD', 'X',\\
n'MPG', 'X',\n'MPH', 'M',\n'MPI', 'X',\n'MPJ', 'M'\
,\n'MPL', 'X',\n'MPN', 'X',\n'MPO', 'X',\n'MPP', '\
X',\n'MPQ', 'G',\n'MPR', 'X',\n'MPS', 'X',\n'MQ0',\
 'X',\n'MQ7', 'X',\n'MQ8', 'X',\n'MQ9', 'X',\n'MQI\
', 'X',\n'MR2', 'X',\n'MRC', 'X',\n'MRM', 'X',\n'M\
RP', 'X',\n'MS2', 'X',\n'MSA', 'X',\n'MSB', 'X',\n\
'MSD', 'X',\n'MSE', 'M',\n'MSF', 'X',\n'MSI', 'X',\
\n'MSO', 'M',\n'MSQ', 'X',\n'MST', 'X',\n'MSU', 'X\
',\n'MTA', 'X',\n'MTB', 'X',\n'MTC', 'X',\n'MTD', \
'X',\n'MTE', 'X',\n'MTF', 'X',\n'MTG', 'X',\n'MTO'\
, 'X',\n'MTS', 'X',\n'MTT', 'X',\n'MTX', 'X',\n'MT\
Y', 'Y',\n'MUG', 'X',\n'MUP', 'X',\n'MUR', 'X',\n'\
MVA', 'V',\n'MW1', 'X',\n'MW2', 'X',\n'MXA', 'X',\\
n'MXY', 'X',\n'MYA', 'X',\n'MYC', 'X',\n'MYG', 'X'\
,\n'MYR', 'X',\n'MYS', 'X',\n'MYT', 'X',\n'MZM', '\
X',\n'N1T', 'X',\n'N25', 'X',\n'N2B', 'X',\n'N3T',\
 'X',\n'N4B', 'X',\n'NA2', 'X',\n'NA5', 'X',\n'NA6\
', 'X',\n'NAA', 'X',\n'NAB', 'X',\n'NAC', 'X',\n'N\
AD', 'X',\n'NAE', 'X',\n'NAF', 'X',\n'NAG', 'X',\n\
'NAH', 'X',\n'NAI', 'X',\n'NAL', 'A',\n'NAM', 'A',\
\n'NAN', 'X',\n'NAO', 'X',\n'NAP', 'X',\n'NAQ', 'X\
',\n'NAR', 'X',\n'NAS', 'X',\n'NAU', 'X',\n'NAV', \
'X',\n'NAW', 'X',\n'NAX', 'X',\n'NAY', 'X',\n'NBA'\
, 'X',\n'NBD', 'X',\n'NBE', 'X',\n'NBG', 'X',\n'NB\
N', 'X',\n'NBP', 'X',\n'NBS', 'X',\n'NBU', 'X',\n'\
NCA', 'X',\n'NCB', 'A',\n'NCD', 'X',\n'NCH', 'X',\\
n'NCM', 'X',\n'NCN', 'X',\n'NCO', 'X',\n'NCR', 'X'\
,\n'NCS', 'X',\n'ND4', 'X',\n'NDA', 'X',\n'NDC', '\
X',\n'NDD', 'X',\n'NDO', 'X',\n'NDP', 'X',\n'NDT',\
 'X',\n'NEA', 'X',\n'NEB', 'X',\n'NED', 'X',\n'NEM\
', 'H',\n'NEN', 'X',\n'NEO', 'X',\n'NEP', 'H',\n'N\
EQ', 'X',\n'NES', 'X',\n'NET', 'X',\n'NEV', 'X',\n\
'NFA', 'F',\n'NFE', 'X',\n'NFG', 'X',\n'NFP', 'X',\
\n'NFS', 'X',\n'NG6', 'X',\n'NGA', 'X',\n'NGL', 'X\
',\n'NGM', 'X',\n'NGO', 'X',\n'NGP', 'X',\n'NGT', \
'X',\n'NGU', 'X',\n'NH2', 'X',\n'NH3', 'X',\n'NH4'\
, 'X',\n'NHD', 'X',\n'NHE', 'X',\n'NHM', 'X',\n'NH\
P', 'X',\n'NHR', 'X',\n'NHS', 'X',\n'NI1', 'X',\n'\
NI2', 'X',\n'NIC', 'X',\n'NID', 'X',\n'NIK', 'X',\\
n'NIO', 'X',\n'NIP', 'X',\n'NIT', 'X',\n'NIU', 'X'\
,\n'NIY', 'Y',\n'NLA', 'X',\n'NLE', 'L',\n'NLG', '\
X',\n'NLN', 'L',\n'NLP', 'L',\n'NM1', 'X',\n'NMA',\
 'A',\n'NMB', 'X',\n'NMC', 'G',\n'NMD', 'X',\n'NME\
', 'X',\n'NMN', 'X',\n'NMO', 'X',\n'NMQ', 'X',\n'N\
MX', 'X',\n'NMY', 'X',\n'NNH', 'R',\n'NNO', 'X',\n\
'NO2', 'X',\n'NO3', 'X',\n'NOA', 'X',\n'NOD', 'X',\
\n'NOJ', 'X',\n'NON', 'X',\n'NOP', 'X',\n'NOR', 'X\
',\n'NOS', 'X',\n'NOV', 'X',\n'NOX', 'X',\n'NP3', \
'X',\n'NPA', 'X',\n'NPC', 'X',\n'NPD', 'X',\n'NPE'\
, 'X',\n'NPF', 'X',\n'NPH', 'C',\n'NPI', 'X',\n'NP\
L', 'X',\n'NPN', 'X',\n'NPO', 'X',\n'NPP', 'X',\n'\
NPT', 'X',\n'NPY', 'X',\n'NRG', 'R',\n'NRI', 'X',\\
n'NS1', 'X',\n'NS5', 'X',\n'NSP', 'X',\n'NTA', 'X'\
,\n'NTB', 'X',\n'NTC', 'X',\n'NTH', 'X',\n'NTM', '\
X',\n'NTP', 'X',\n'NTS', 'X',\n'NTU', 'X',\n'NTZ',\
 'X',\n'NU1', 'X',\n'NVA', 'V',\n'NVI', 'X',\n'NVP\
', 'X',\n'NW1', 'X',\n'NYP', 'X',\n'O4M', 'X',\n'O\
AA', 'X',\n'OAI', 'X',\n'OAP', 'X',\n'OAR', 'X',\n\
'OAS', 'S',\n'OBA', 'X',\n'OBN', 'X',\n'OC1', 'X',\
\n'OC2', 'X',\n'OC3', 'X',\n'OC4', 'X',\n'OC5', 'X\
',\n'OC6', 'X',\n'OC7', 'X',\n'OCL', 'X',\n'OCM', \
'X',\n'OCN', 'X',\n'OCO', 'X',\n'OCP', 'X',\n'OCS'\
, 'C',\n'OCT', 'X',\n'OCV', 'K',\n'OCY', 'C',\n'OD\
A', 'X',\n'ODS', 'X',\n'OES', 'X',\n'OET', 'X',\n'\
OF1', 'X',\n'OF2', 'X',\n'OF3', 'X',\n'OFL', 'X',\\
n'OFO', 'X',\n'OHE', 'X',\n'OHO', 'X',\n'OHT', 'X'\
,\n'OIC', 'X',\n'OIP', 'X',\n'OKA', 'X',\n'OLA', '\
X',\n'OLE', 'X',\n'OLI', 'X',\n'OLO', 'X',\n'OMB',\
 'X',\n'OMC', 'X',\n'OMD', 'X',\n'OME', 'X',\n'OMG\
', 'X',\n'OMP', 'X',\n'OMT', 'M',\n'OMU', 'X',\n'O\
NE', 'X',\n'ONL', 'L',\n'ONP', 'X',\n'OPA', 'X',\n\
'OPD', 'X',\n'OPE', 'X',\n'OPG', 'X',\n'OPH', 'X',\
\n'OPN', 'X',\n'OPP', 'X',\n'OPR', 'R',\n'ORN', 'X\
',\n'ORO', 'X',\n'ORP', 'X',\n'OSB', 'X',\n'OSS', \
'X',\n'OTA', 'X',\n'OTB', 'X',\n'OTE', 'X',\n'OTG'\
, 'X',\n'OUT', 'X',\n'OVA', 'X',\n'OWQ', 'X',\n'OX\
A', 'X',\n'OXE', 'X',\n'OXI', 'X',\n'OXL', 'X',\n'\
OXM', 'X',\n'OXN', 'X',\n'OXO', 'X',\n'OXP', 'X',\\
n'OXS', 'X',\n'OXY', 'X',\n'P11', 'A',\n'P24', 'X'\
,\n'P28', 'X',\n'P2P', 'X',\n'P2U', 'X',\n'P3M', '\
X',\n'P4C', 'X',\n'P4P', 'X',\n'P5P', 'X',\n'P6G',\
 'X',\n'PA1', 'X',\n'PA2', 'X',\n'PA3', 'X',\n'PA4\
', 'X',\n'PA5', 'X',\n'PAA', 'X',\n'PAB', 'X',\n'P\
AC', 'X',\n'PAD', 'X',\n'PAE', 'X',\n'PAG', 'X',\n\
'PAH', 'X',\n'PAI', 'X',\n'PAL', 'D',\n'PAM', 'X',\
\n'PAN', 'X',\n'PAO', 'X',\n'PAP', 'A',\n'PAQ', 'F\
',\n'PAR', 'X',\n'PAS', 'X',\n'PAT', 'W',\n'PBA', \
'X',\n'PBB', 'X',\n'PBC', 'X',\n'PBF', 'F',\n'PBG'\
, 'X',\n'PBI', 'X',\n'PBM', 'X',\n'PBN', 'X',\n'PB\
P', 'X',\n'PBR', 'X',\n'PBZ', 'X',\n'PC2', 'X',\n'\
PCA', 'E',\n'PCB', 'X',\n'PCD', 'X',\n'PCE', 'X',\\
n'PCG', 'X',\n'PCH', 'X',\n'PCL', 'X',\n'PCM', 'X'\
,\n'PCP', 'X',\n'PCR', 'X',\n'PCS', 'X',\n'PCU', '\
X',\n'PCV', 'X',\n'PCY', 'X',\n'PD1', 'X',\n'PDA',\
 'X',\n'PDC', 'X',\n'PDD', 'A',\n'PDE', 'A',\n'PDI\
', 'X',\n'PDL', 'A',\n'PDN', 'X',\n'PDO', 'X',\n'P\
DP', 'X',\n'PDT', 'X',\n'PDU', 'X',\n'PE2', 'X',\n\
'PE6', 'X',\n'PEA', 'X',\n'PEB', 'X',\n'PEC', 'X',\
\n'PED', 'X',\n'PEE', 'X',\n'PEF', 'X',\n'PEG', 'X\
',\n'PEL', 'X',\n'PEO', 'X',\n'PEP', 'X',\n'PEQ', \
'X',\n'PER', 'X',\n'PET', 'X',\n'PFB', 'X',\n'PFC'\
, 'X',\n'PFG', 'X',\n'PFL', 'X',\n'PFM', 'X',\n'PF\
Z', 'X',\n'PG4', 'X',\n'PG5', 'X',\n'PG6', 'X',\n'\
PGA', 'X',\n'PGC', 'X',\n'PGD', 'X',\n'PGE', 'X',\\
n'PGG', 'G',\n'PGH', 'X',\n'PGL', 'X',\n'PGO', 'X'\
,\n'PGP', 'X',\n'PGQ', 'X',\n'PGR', 'X',\n'PGS', '\
X',\n'PGU', 'X',\n'PGX', 'X',\n'PGY', 'G',\n'PH1',\
 'X',\n'PH2', 'X',\n'PH3', 'X',\n'PHA', 'F',\n'PHB\
', 'X',\n'PHC', 'X',\n'PHD', 'X',\n'PHE', 'F',\n'P\
HG', 'X',\n'PHH', 'X',\n'PHI', 'F',\n'PHL', 'F',\n\
'PHM', 'X',\n'PHN', 'X',\n'PHO', 'X',\n'PHP', 'X',\
\n'PHQ', 'X',\n'PHS', 'H',\n'PHT', 'X',\n'PHW', 'P\
',\n'PHY', 'X',\n'PI1', 'X',\n'PI2', 'X',\n'PI3', \
'X',\n'PI4', 'X',\n'PI5', 'X',\n'PI6', 'X',\n'PI7'\
, 'X',\n'PI8', 'X',\n'PI9', 'X',\n'PIA', 'X',\n'PI\
B', 'X',\n'PIC', 'X',\n'PID', 'X',\n'PIG', 'X',\n'\
PIH', 'X',\n'PIM', 'X',\n'PIN', 'X',\n'PIO', 'X',\\
n'PIP', 'X',\n'PIQ', 'X',\n'PIR', 'X',\n'PIV', 'X'\
,\n'PKF', 'X',\n'PL1', 'X',\n'PL9', 'X',\n'PLA', '\
D',\n'PLC', 'X',\n'PLE', 'L',\n'PLG', 'G',\n'PLH',\
 'X',\n'PLM', 'X',\n'PLP', 'X',\n'PLS', 'S',\n'PLT\
', 'W',\n'PLU', 'L',\n'PLY', 'X',\n'PMA', 'X',\n'P\
MB', 'X',\n'PMC', 'X',\n'PME', 'F',\n'PML', 'X',\n\
'PMM', 'X',\n'PMO', 'X',\n'PMP', 'X',\n'PMS', 'X',\
\n'PMY', 'X',\n'PN2', 'X',\n'PNA', 'X',\n'PNB', 'X\
',\n'PNC', 'G',\n'PND', 'X',\n'PNE', 'A',\n'PNF', \
'X',\n'PNG', 'X',\n'PNI', 'X',\n'PNL', 'X',\n'PNM'\
, 'X',\n'PNN', 'X',\n'PNO', 'X',\n'PNP', 'X',\n'PN\
Q', 'X',\n'PNS', 'X',\n'PNT', 'X',\n'PNU', 'X',\n'\
PO2', 'X',\n'PO4', 'X',\n'POB', 'X',\n'POC', 'X',\\
n'POL', 'X',\n'POM', 'P',\n'PON', 'X',\n'POP', 'X'\
,\n'POR', 'X',\n'POS', 'X',\n'PP1', 'X',\n'PP2', '\
X',\n'PP3', 'A',\n'PP4', 'X',\n'PP5', 'X',\n'PP6',\
 'X',\n'PP7', 'X',\n'PP8', 'N',\n'PP9', 'X',\n'PPB\
', 'X',\n'PPC', 'X',\n'PPD', 'X',\n'PPE', 'E',\n'P\
PG', 'X',\n'PPH', 'F',\n'PPI', 'X',\n'PPJ', 'V',\n\
'PPL', 'X',\n'PPM', 'X',\n'PPN', 'A',\n'PPO', 'X',\
\n'PPP', 'X',\n'PPQ', 'X',\n'PPR', 'X',\n'PPS', 'X\
',\n'PPT', 'X',\n'PPU', 'X',\n'PPX', 'F',\n'PPY', \
'X',\n'PPZ', 'X',\n'PQ0', 'X',\n'PQN', 'X',\n'PQQ'\
, 'X',\n'PR1', 'X',\n'PR2', 'X',\n'PR3', 'X',\n'PR\
A', 'X',\n'PRB', 'X',\n'PRC', 'X',\n'PRD', 'X',\n'\
PRE', 'X',\n'PRF', 'X',\n'PRH', 'X',\n'PRI', 'P',\\
n'PRL', 'X',\n'PRN', 'X',\n'PRO', 'P',\n'PRP', 'X'\
,\n'PRR', 'A',\n'PRS', 'P',\n'PRZ', 'X',\n'PS0', '\
X',\n'PSA', 'X',\n'PSD', 'X',\n'PSE', 'X',\n'PSF',\
 'S',\n'PSG', 'X',\n'PSI', 'X',\n'PSO', 'X',\n'PSQ\
', 'X',\n'PSS', 'X',\n'PST', 'X',\n'PSU', 'X',\n'P\
T1', 'X',\n'PT3', 'X',\n'PTA', 'X',\n'PTC', 'X',\n\
'PTD', 'X',\n'PTE', 'X',\n'PTH', 'Y',\n'PTL', 'X',\
\n'PTM', 'Y',\n'PTN', 'X',\n'PTO', 'X',\n'PTP', 'X\
',\n'PTR', 'Y',\n'PTS', 'X',\n'PTT', 'X',\n'PTU', \
'X',\n'PTY', 'X',\n'PUA', 'X',\n'PUB', 'X',\n'PUR'\
, 'X',\n'PUT', 'X',\n'PVA', 'X',\n'PVB', 'X',\n'PV\
H', 'H',\n'PVL', 'X',\n'PXA', 'X',\n'PXF', 'X',\n'\
PXG', 'X',\n'PXP', 'X',\n'PXY', 'X',\n'PXZ', 'X',\\
n'PY2', 'X',\n'PY4', 'X',\n'PY5', 'X',\n'PY6', 'X'\
,\n'PYA', 'A',\n'PYC', 'X',\n'PYD', 'X',\n'PYE', '\
X',\n'PYL', 'X',\n'PYM', 'X',\n'PYO', 'X',\n'PYP',\
 'X',\n'PYQ', 'X',\n'PYR', 'X',\n'PYS', 'X',\n'PYT\
', 'X',\n'PYX', 'X',\n'PYY', 'X',\n'PYZ', 'X',\n'P\
ZQ', 'X',\n'Q82', 'X',\n'QNC', 'X',\n'QND', 'X',\n\
'QSI', 'Q',\n'QTR', 'X',\n'QUA', 'X',\n'QUE', 'X',\
\n'QUI', 'X',\n'QUO', 'X',\n'R11', 'X',\n'R12', 'X\
',\n'R13', 'X',\n'R18', 'X',\n'R1P', 'X',\n'R56', \
'X',\n'R5P', 'X',\n'RA2', 'X',\n'RAD', 'X',\n'RAI'\
, 'X',\n'RAL', 'X',\n'RAM', 'X',\n'RAN', 'X',\n'RA\
P', 'X',\n'RBF', 'X',\n'RBU', 'X',\n'RCA', 'X',\n'\
RCL', 'X',\n'RCO', 'X',\n'RDC', 'X',\n'RDF', 'W',\\
n'RE9', 'X',\n'REA', 'X',\n'RED', 'K',\n'REO', 'X'\
,\n'REP', 'X',\n'RET', 'X',\n'RFA', 'X',\n'RFB', '\
X',\n'RFL', 'X',\n'RFP', 'X',\n'RG1', 'X',\n'RGS',\
 'X',\n'RH1', 'X',\n'RHA', 'X',\n'RHC', 'X',\n'RHD\
', 'X',\n'RHM', 'X',\n'RHO', 'X',\n'RHQ', 'X',\n'R\
HS', 'X',\n'RIA', 'X',\n'RIB', 'X',\n'RIC', 'X',\n\
'RIF', 'X',\n'RIN', 'X',\n'RIP', 'X',\n'RIT', 'X',\
\n'RMB', 'X',\n'RMN', 'X',\n'RMP', 'X',\n'RNG', 'X\
',\n'RNS', 'X',\n'RNT', 'X',\n'RO2', 'X',\n'RO4', \
'X',\n'ROC', 'N',\n'ROI', 'X',\n'ROM', 'X',\n'RON'\
, 'V',\n'ROP', 'X',\n'ROS', 'X',\n'ROX', 'X',\n'RP\
A', 'X',\n'RPD', 'X',\n'RPH', 'X',\n'RPL', 'X',\n'\
RPP', 'X',\n'RPR', 'X',\n'RPX', 'X',\n'RQ3', 'X',\\
n'RR1', 'X',\n'RR6', 'X',\n'RRS', 'X',\n'RS1', 'X'\
,\n'RS2', 'X',\n'RS7', 'X',\n'RSS', 'X',\n'RTA', '\
X',\n'RTB', 'X',\n'RTC', 'X',\n'RTL', 'X',\n'RUB',\
 'X',\n'RUN', 'X',\n'RWJ', 'X',\n'RXP', 'X',\n'S02\
', 'X',\n'S11', 'X',\n'S1H', 'S',\n'S27', 'X',\n'S\
2C', 'C',\n'S3P', 'X',\n'S4U', 'X',\n'S57', 'X',\n\
'S58', 'X',\n'S5H', 'X',\n'S6G', 'X',\n'S80', 'X',\
\n'SAA', 'X',\n'SAB', 'X',\n'SAC', 'S',\n'SAD', 'X\
',\n'SAE', 'X',\n'SAF', 'X',\n'SAH', 'C',\n'SAI', \
'C',\n'SAL', 'X',\n'SAM', 'M',\n'SAN', 'X',\n'SAP'\
, 'X',\n'SAR', 'X',\n'SAS', 'X',\n'SB1', 'X',\n'SB\
2', 'X',\n'SB3', 'X',\n'SB4', 'X',\n'SB5', 'X',\n'\
SB6', 'X',\n'SBA', 'L',\n'SBB', 'X',\n'SBD', 'A',\\
n'SBI', 'X',\n'SBL', 'A',\n'SBN', 'X',\n'SBO', 'X'\
,\n'SBR', 'X',\n'SBS', 'X',\n'SBT', 'X',\n'SBU', '\
X',\n'SBX', 'X',\n'SC4', 'X',\n'SCA', 'X',\n'SCC',\
 'X',\n'SCD', 'X',\n'SCH', 'C',\n'SCI', 'X',\n'SCL\
', 'X',\n'SCM', 'X',\n'SCN', 'X',\n'SCO', 'X',\n'S\
CP', 'S',\n'SCR', 'X',\n'SCS', 'X',\n'SCV', 'C',\n\
'SCY', 'C',\n'SD8', 'X',\n'SDK', 'X',\n'SDZ', 'X',\
\n'SE4', 'X',\n'SEA', 'X',\n'SEB', 'S',\n'SEC', 'X\
',\n'SEG', 'A',\n'SEI', 'X',\n'SEL', 'S',\n'SEM', \
'X',\n'SEO', 'X',\n'SEP', 'S',\n'SER', 'S',\n'SES'\
, 'X',\n'SET', 'S',\n'SEU', 'X',\n'SF4', 'X',\n'SF\
G', 'X',\n'SFN', 'X',\n'SFO', 'X',\n'SGA', 'X',\n'\
SGC', 'X',\n'SGL', 'X',\n'SGM', 'X',\n'SGN', 'X',\\
n'SGP', 'X',\n'SHA', 'X',\n'SHC', 'X',\n'SHF', 'X'\
,\n'SHH', 'X',\n'SHP', 'G',\n'SHR', 'E',\n'SHT', '\
T',\n'SHU', 'X',\n'SI2', 'X',\n'SIA', 'X',\n'SIF',\
 'X',\n'SIG', 'X',\n'SIH', 'X',\n'SIM', 'X',\n'SIN\
', 'X',\n'SKD', 'X',\n'SKF', 'X',\n'SLB', 'X',\n'S\
LE', 'X',\n'SLZ', 'K',\n'SMA', 'X',\n'SMC', 'C',\n\
'SME', 'M',\n'SML', 'X',\n'SMM', 'M',\n'SMN', 'X',\
\n'SMP', 'X',\n'SMS', 'X',\n'SN1', 'X',\n'SN6', 'X\
',\n'SN7', 'X',\n'SNC', 'C',\n'SNN', 'X',\n'SNP', \
'X',\n'SO1', 'X',\n'SO2', 'X',\n'SO3', 'X',\n'SO4'\
, 'X',\n'SOA', 'X',\n'SOC', 'C',\n'SOM', 'X',\n'SO\
R', 'X',\n'SOT', 'X',\n'SOX', 'X',\n'SPA', 'X',\n'\
SPB', 'X',\n'SPC', 'X',\n'SPD', 'X',\n'SPE', 'X',\\
n'SPG', 'X',\n'SPH', 'X',\n'SPI', 'X',\n'SPK', 'X'\
,\n'SPM', 'X',\n'SPN', 'X',\n'SPO', 'X',\n'SPP', '\
X',\n'SPS', 'X',\n'SPY', 'X',\n'SQU', 'X',\n'SRA',\
 'X',\n'SRB', 'X',\n'SRD', 'X',\n'SRL', 'X',\n'SRM\
', 'X',\n'SRS', 'X',\n'SRY', 'X',\n'SSA', 'X',\n'S\
SB', 'X',\n'SSG', 'X',\n'SSP', 'X',\n'ST1', 'X',\n\
'ST2', 'X',\n'ST3', 'X',\n'ST4', 'X',\n'ST5', 'X',\
\n'ST6', 'X',\n'STA', 'X',\n'STB', 'X',\n'STE', 'X\
',\n'STG', 'X',\n'STI', 'X',\n'STL', 'X',\n'STN', \
'X',\n'STO', 'X',\n'STP', 'X',\n'STR', 'X',\n'STU'\
, 'X',\n'STY', 'Y',\n'SU1', 'X',\n'SU2', 'X',\n'SU\
C', 'X',\n'SUI', 'X',\n'SUL', 'X',\n'SUR', 'X',\n'\
SVA', 'S',\n'SWA', 'X',\n'T16', 'X',\n'T19', 'X',\\
n'T23', 'X',\n'T29', 'X',\n'T33', 'X',\n'T3P', 'X'\
,\n'T42', 'A',\n'T44', 'X',\n'T5A', 'X',\n'T6A', '\
T',\n'T6P', 'X',\n'T80', 'X',\n'T87', 'X',\n'TA1',\
 'X',\n'TAA', 'X',\n'TAB', 'X',\n'TAC', 'X',\n'TAD\
', 'X',\n'TAF', 'X',\n'TAM', 'X',\n'TAP', 'X',\n'T\
AR', 'X',\n'TAS', 'X',\n'TAU', 'X',\n'TAX', 'X',\n\
'TAZ', 'X',\n'TB9', 'X',\n'TBA', 'X',\n'TBD', 'X',\
\n'TBG', 'G',\n'TBH', 'X',\n'TBM', 'T',\n'TBO', 'X\
',\n'TBP', 'X',\n'TBR', 'X',\n'TBS', 'X',\n'TBT', \
'X',\n'TBU', 'X',\n'TBZ', 'X',\n'TC4', 'X',\n'TCA'\
, 'X',\n'TCB', 'X',\n'TCH', 'X',\n'TCK', 'X',\n'TC\
L', 'X',\n'TCM', 'X',\n'TCN', 'X',\n'TCP', 'X',\n'\
TCR', 'W',\n'TCS', 'X',\n'TCZ', 'X',\n'TDA', 'X',\\
n'TDB', 'X',\n'TDG', 'X',\n'TDP', 'X',\n'TDR', 'X'\
,\n'TDX', 'X',\n'TEA', 'X',\n'TEM', 'X',\n'TEN', '\
X',\n'TEO', 'X',\n'TEP', 'X',\n'TER', 'X',\n'TES',\
 'X',\n'TET', 'X',\n'TFA', 'X',\n'TFB', 'X',\n'TFH\
', 'X',\n'TFI', 'X',\n'TFK', 'X',\n'TFP', 'X',\n'T\
HA', 'X',\n'THB', 'X',\n'THC', 'T',\n'THD', 'X',\n\
'THE', 'X',\n'THF', 'X',\n'THJ', 'X',\n'THK', 'X',\
\n'THM', 'X',\n'THN', 'X',\n'THO', 'T',\n'THP', 'X\
',\n'THQ', 'X',\n'THR', 'T',\n'THS', 'X',\n'THT', \
'X',\n'THU', 'X',\n'THX', 'X',\n'THZ', 'X',\n'TI1'\
, 'X',\n'TI2', 'X',\n'TI3', 'P',\n'TIA', 'X',\n'TI\
H', 'A',\n'TK4', 'X',\n'TLA', 'X',\n'TLC', 'X',\n'\
TLM', 'X',\n'TLN', 'X',\n'TLX', 'X',\n'TM5', 'X',\\
n'TM6', 'X',\n'TMA', 'X',\n'TMB', 'T',\n'TMC', 'X'\
,\n'TMD', 'T',\n'TME', 'X',\n'TMF', 'X',\n'TML', '\
K',\n'TMM', 'X',\n'TMN', 'X',\n'TMP', 'X',\n'TMQ',\
 'X',\n'TMR', 'X',\n'TMT', 'X',\n'TMZ', 'X',\n'TNB\
', 'C',\n'TND', 'X',\n'TNK', 'X',\n'TNP', 'X',\n'T\
NT', 'X',\n'TOA', 'X',\n'TOB', 'X',\n'TOC', 'X',\n\
'TOL', 'X',\n'TOP', 'X',\n'TOS', 'X',\n'TOT', 'X',\
\n'TP1', 'G',\n'TP2', 'P',\n'TP3', 'E',\n'TP4', 'E\
',\n'TP7', 'T',\n'TPA', 'X',\n'TPE', 'X',\n'TPF', \
'X',\n'TPI', 'X',\n'TPL', 'W',\n'TPM', 'X',\n'TPN'\
, 'G',\n'TPO', 'T',\n'TPP', 'X',\n'TPQ', 'A',\n'TP\
R', 'P',\n'TPS', 'X',\n'TPT', 'X',\n'TPV', 'X',\n'\
TPX', 'X',\n'TPY', 'X',\n'TQ3', 'X',\n'TQ4', 'X',\\
n'TQ5', 'X',\n'TQ6', 'X',\n'TR1', 'X',\n'TRA', 'X'\
,\n'TRB', 'X',\n'TRC', 'X',\n'TRD', 'X',\n'TRE', '\
X',\n'TRF', 'W',\n'TRG', 'K',\n'TRH', 'X',\n'TRI',\
 'X',\n'TRJ', 'X',\n'TRM', 'X',\n'TRN', 'W',\n'TRO\
', 'W',\n'TRP', 'W',\n'TRQ', 'X',\n'TRS', 'X',\n'T\
RX', 'W',\n'TRZ', 'X',\n'TS2', 'X',\n'TS3', 'X',\n\
'TS4', 'X',\n'TS5', 'X',\n'TSA', 'X',\n'TSB', 'X',\
\n'TSI', 'X',\n'TSM', 'X',\n'TSN', 'X',\n'TSP', 'X\
',\n'TSU', 'X',\n'TTA', 'X',\n'TTE', 'X',\n'TTN', \
'X',\n'TTO', 'X',\n'TTP', 'X',\n'TTX', 'X',\n'TXL'\
, 'X',\n'TYA', 'Y',\n'TYB', 'Y',\n'TYD', 'X',\n'TY\
I', 'Y',\n'TYL', 'X',\n'TYM', 'W',\n'TYN', 'Y',\n'\
TYQ', 'Y',\n'TYR', 'Y',\n'TYS', 'Y',\n'TYV', 'X',\\
n'TYY', 'A',\n'TZB', 'X',\n'TZC', 'X',\n'TZE', 'X'\
,\n'TZL', 'X',\n'TZO', 'X',\n'TZP', 'X',\n'U01', '\
X',\n'U02', 'X',\n'U03', 'X',\n'U04', 'X',\n'U05',\
 'X',\n'U0E', 'X',\n'U10', 'X',\n'U18', 'X',\n'U2G\
', 'X',\n'U3P', 'X',\n'U49', 'X',\n'U55', 'X',\n'U\
5P', 'X',\n'U66', 'X',\n'U89', 'X',\n'U8U', 'X',\n\
'UAA', 'X',\n'UAG', 'A',\n'UAP', 'X',\n'UAR', 'X',\
\n'UC1', 'X',\n'UC2', 'X',\n'UC3', 'X',\n'UC4', 'X\
',\n'UD1', 'X',\n'UD2', 'X',\n'UDP', 'X',\n'UDX', \
'X',\n'UFG', 'X',\n'UFM', 'X',\n'UFP', 'X',\n'UGA'\
, 'X',\n'UIN', 'X',\n'UKP', 'A',\n'UM3', 'X',\n'UM\
A', 'A',\n'UMG', 'X',\n'UMP', 'X',\n'UNA', 'X',\n'\
UND', 'X',\n'UNI', 'X',\n'UNK', 'X',\n'UNN', 'X',\\
n'UNX', 'X',\n'UP5', 'X',\n'UP6', 'X',\n'UPA', 'X'\
,\n'UPF', 'X',\n'UPG', 'X',\n'UPP', 'X',\n'UQ1', '\
X',\n'UQ2', 'X',\n'UQ6', 'X',\n'UR2', 'X',\n'URA',\
 'X',\n'URE', 'X',\n'URF', 'X',\n'URI', 'X',\n'URS\
', 'X',\n'UTP', 'X',\n'UVC', 'X',\n'UVW', 'X',\n'V\
35', 'X',\n'V36', 'X',\n'V4O', 'X',\n'V7O', 'X',\n\
'VAA', 'V',\n'VAC', 'X',\n'VAD', 'V',\n'VAF', 'V',\
\n'VAG', 'X',\n'VAL', 'V',\n'VAN', 'X',\n'VAS', 'X\
',\n'VAX', 'X',\n'VDX', 'X',\n'VDY', 'X',\n'VG1', \
'X',\n'VIB', 'X',\n'VIR', 'X',\n'VIT', 'X',\n'VK3'\
, 'X',\n'VO3', 'X',\n'VO4', 'X',\n'VS1', 'F',\n'VS\
2', 'F',\n'VS3', 'F',\n'VS4', 'F',\n'VXA', 'X',\n'\
W01', 'X',\n'W02', 'X',\n'W03', 'X',\n'W11', 'X',\\
n'W33', 'X',\n'W35', 'X',\n'W42', 'X',\n'W43', 'X'\
,\n'W54', 'X',\n'W56', 'X',\n'W59', 'X',\n'W71', '\
X',\n'W84', 'X',\n'W8R', 'X',\n'W91', 'X',\n'WAY',\
 'X',\n'WCC', 'X',\n'WO2', 'X',\n'WO4', 'X',\n'WRB\
', 'X',\n'WRR', 'X',\n'WRS', 'X',\n'WW7', 'X',\n'X\
2F', 'X',\n'X7O', 'X',\n'XAA', 'X',\n'XAN', 'X',\n\
'XAO', 'X',\n'XBB', 'X',\n'XBP', 'X',\n'XDN', 'X',\
\n'XDP', 'X',\n'XIF', 'X',\n'XIM', 'X',\n'XK2', 'X\
',\n'XL1', 'X',\n'XLS', 'X',\n'XMP', 'X',\n'XN1', \
'X',\n'XN2', 'X',\n'XN3', 'X',\n'XUL', 'X',\n'XV6'\
, 'X',\n'XYD', 'X',\n'XYH', 'X',\n'XYL', 'X',\n'XY\
P', 'X',\n'XYS', 'X',\n'YOF', 'Y',\n'YRR', 'X',\n'\
YT3', 'X',\n'YZ9', 'X',\n'Z34', 'G',\n'Z5A', 'X',\\
n'ZAF', 'X',\n'ZAP', 'X',\n'ZEB', 'X',\n'ZEN', 'X'\
,\n'ZES', 'X',\n'ZID', 'X',\n'ZMR', 'X',\n'ZN3', '\
X',\n'ZNH', 'X',\n'ZNO', 'X',\n'ZO3', 'X',\n'ZPR',\
 'P',\n'ZRA', 'A',\n'ZST', 'X',\n'ZYA', 'A',\n\n\n\
'ASN','N');\n} \n\n\nsub file2head\n      {\n	my $\
file = shift;\n	my $size = shift;\n	my $f= new Fil\
eHandle;\n	my $line;\n	open ($f,$file);\n	read ($f\
,$line, $size);\n	close ($f);\n	return $line;\n   \
   }\nsub file2tail\n      {\n	my $file = shift;\n\
	my $size = shift;\n	my $f= new FileHandle;\n	my $\
line;\n	\n	open ($f,$file);\n	seek ($f,$size*-1, 2\
);\n	read ($f,$line, $size);\n	close ($f);\n	retur\
n $line;\n      }\n\n\nsub vtmpnam\n      {\n	my $\
r=rand(100000);\n	my $f=\"file.$r.$$\";\n	while (-\
e $f)\n	  {\n	    $f=vtmpnam();\n	  }\n	push (@TMP\
FILE_LIST, $f);\n	return $f;\n      }\n\nsub myexi\
t\n  {\n    my $code=@_[0];\n    if ($CLEAN_EXIT_S\
TARTED==1){return;}\n    else {$CLEAN_EXIT_STARTED\
=1;}\n    ### ONLY BARE EXIT\n    exit ($code);\n \
 }\nsub set_error_lock\n    {\n      my $name = sh\
ift;\n      my $pid=$$;\n\n      \n      &lock4tc \
($$,\"LERROR\", \"LSET\", \"$$ -- ERROR: $name $PR\
OGRAM\\n\");\n      return;\n    }\nsub set_lock\n\
  {\n    my $pid=shift;\n    my $msg= shift;\n    \
my $p=getppid();\n    &lock4tc ($pid,\"LLOCK\",\"L\
RESET\",\"$p$msg\\n\");\n  }\nsub unset_lock\n   {\
\n     \n    my $pid=shift;\n    &lock4tc ($pid,\"\
LLOCK\",\"LRELEASE\",\"\");\n  }\nsub shift_lock\n\
  {\n    my $from=shift;\n    my $to=shift;\n    m\
y $from_type=shift;\n    my $to_type=shift;\n    m\
y $action=shift;\n    my $msg;\n    \n    if (!&lo\
ck4tc($from, $from_type, \"LCHECK\", \"\")){return\
 0;}\n    $msg=&lock4tc ($from, $from_type, \"LREA\
D\", \"\");\n    &lock4tc ($from, $from_type,\"LRE\
LEASE\", $msg);\n    &lock4tc ($to, $to_type, $act\
ion, $msg);\n    return;\n  }\nsub isshellpid\n  {\
\n    my $p=shift;\n    if (!lock4tc ($p, \"LLOCK\\
", \"LCHECK\")){return 0;}\n    else\n      {\n	my\
 $c=lock4tc($p, \"LLOCK\", \"LREAD\");\n	if ( $c=~\
/-SHELL-/){return 1;}\n      }\n    return 0;\n  }\
\nsub isrootpid\n  {\n    if(lock4tc (getppid(), \\
"LLOCK\", \"LCHECK\")){return 0;}\n    else {retur\
n 1;}\n  }\nsub lock4tc\n	{\n	  my ($pid,$type,$ac\
tion,$value)=@_;\n	  my $fname;\n	  my $host=hostn\
ame;\n	  \n	  if ($type eq \"LLOCK\"){$fname=\"$LO\
CKDIR/.$pid.$host.lock4tcoffee\";}\n	  elsif ( $ty\
pe eq \"LERROR\"){ $fname=\"$LOCKDIR/.$pid.$host.e\
rror4tcoffee\";}\n	  elsif ( $type eq \"LWARNING\"\
){ $fname=\"$LOCKDIR/.$pid.$host.warning4tcoffee\"\
;}\n	  \n	  if ($debug_lock)\n	    {\n	      print\
 STDERR \"\\n\\t---lock4tc(tcg): $action => $fname\
 =>$value (RD: $LOCKDIR)\\n\";\n	    }\n\n	  if   \
 ($action eq \"LCHECK\") {return -e $fname;}\n	  e\
lsif ($action eq \"LREAD\"){return file2string($fn\
ame);}\n	  elsif ($action eq \"LSET\") {return str\
ing2file ($value, $fname, \">>\");}\n	  elsif ($ac\
tion eq \"LRESET\") {return string2file ($value, $\
fname, \">\");}\n	  elsif ($action eq \"LRELEASE\"\
) \n	    {\n	      if ( $debug_lock)\n		{\n		  my \
$g=new FileHandle;\n		  open ($g, \">>$fname\");\n\
		  print $g \"\\nDestroyed by $$\\n\";\n		  close\
 ($g);\n		  safe_system (\"mv $fname $fname.old\")\
;\n		}\n	      else\n		{\n		  unlink ($fname);\n		\
}\n	    }\n	  return \"\";\n	}\n	\nsub file2string\
\n	{\n	  my $file=@_[0];\n	  my $f=new FileHandle;\
\n	  my $r;\n	  open ($f, \"$file\");\n	  while (<\
$f>){$r.=$_;}\n	  close ($f);\n	  return $r;\n	}\n\
sub string2file \n    {\n    my ($s,$file,$mode)=@\
_;\n    my $f=new FileHandle;\n    \n    open ($f,\
 \"$mode$file\");\n    print $f  \"$s\";\n    clos\
e ($f);\n  }\n\nBEGIN\n    {\n      srand;\n    \n\
      $SIG{'SIGUP'}='signal_cleanup';\n      $SIG{\
'SIGINT'}='signal_cleanup';\n      $SIG{'SIGQUIT'}\
='signal_cleanup';\n      $SIG{'SIGILL'}='signal_c\
leanup';\n      $SIG{'SIGTRAP'}='signal_cleanup';\\
n      $SIG{'SIGABRT'}='signal_cleanup';\n      $S\
IG{'SIGEMT'}='signal_cleanup';\n      $SIG{'SIGFPE\
'}='signal_cleanup';\n      \n      $SIG{'SIGKILL'\
}='signal_cleanup';\n      $SIG{'SIGPIPE'}='signal\
_cleanup';\n      $SIG{'SIGSTOP'}='signal_cleanup'\
;\n      $SIG{'SIGTTIN'}='signal_cleanup';\n      \
$SIG{'SIGXFSZ'}='signal_cleanup';\n      $SIG{'SIG\
INFO'}='signal_cleanup';\n      \n      $SIG{'SIGB\
US'}='signal_cleanup';\n      $SIG{'SIGALRM'}='sig\
nal_cleanup';\n      $SIG{'SIGTSTP'}='signal_clean\
up';\n      $SIG{'SIGTTOU'}='signal_cleanup';\n   \
   $SIG{'SIGVTALRM'}='signal_cleanup';\n      $SIG\
{'SIGUSR1'}='signal_cleanup';\n\n\n      $SIG{'SIG\
SEGV'}='signal_cleanup';\n      $SIG{'SIGTERM'}='s\
ignal_cleanup';\n      $SIG{'SIGCONT'}='signal_cle\
anup';\n      $SIG{'SIGIO'}='signal_cleanup';\n   \
   $SIG{'SIGPROF'}='signal_cleanup';\n      $SIG{'\
SIGUSR2'}='signal_cleanup';\n\n      $SIG{'SIGSYS'\
}='signal_cleanup';\n      $SIG{'SIGURG'}='signal_\
cleanup';\n      $SIG{'SIGCHLD'}='signal_cleanup';\
\n      $SIG{'SIGXCPU'}='signal_cleanup';\n      $\
SIG{'SIGWINCH'}='signal_cleanup';\n      \n      $\
SIG{'INT'}='signal_cleanup';\n      $SIG{'TERM'}='\
signal_cleanup';\n      $SIG{'KILL'}='signal_clean\
up';\n      $SIG{'QUIT'}='signal_cleanup';\n      \
\n      our $debug_lock=$ENV{\"DEBUG_LOCK\"};\n   \
   \n      \n      \n      \n      foreach my $a (\
@ARGV){$CL.=\" $a\";}\n      if ( $debug_lock ){pr\
int STDERR \"\\n\\n\\n********** START PG: $PROGRA\
M *************\\n\";}\n      if ( $debug_lock ){p\
rint STDERR \"\\n\\n\\n**********(tcg) LOCKDIR: $L\
OCKDIR $$ *************\\n\";}\n      if ( $debug_\
lock ){print STDERR \"\\n --- $$ -- $CL\\n\";}\n  \
    \n	     \n      \n      \n    }\nsub flush_err\
or\n  {\n    my $msg=shift;\n    return add_error \
($EXIT_FAILURE,$$, $$,getppid(), $msg, $CL);\n  }\\
nsub add_error \n  {\n    my $code=shift;\n    my \
$rpid=shift;\n    my $pid=shift;\n    my $ppid=shi\
ft;\n    my $type=shift;\n    my $com=shift;\n    \
\n    $ERROR_DONE=1;\n    lock4tc ($rpid, \"LERROR\
\",\"LSET\",\"$pid -- ERROR: $type\\n\");\n    loc\
k4tc ($$, \"LERROR\",\"LSET\", \"$pid -- COM: $com\
\\n\");\n    lock4tc ($$, \"LERROR\",\"LSET\", \"$\
pid -- STACK: $ppid -> $pid\\n\");\n   \n    retur\
n $code;\n  }\nsub add_warning \n  {\n    my $rpid\
=shift;\n    my $pid =shift;\n    my $command=shif\
t;\n    my $msg=\"$$ -- WARNING: $command\\n\";\n \
   print STDERR \"$msg\";\n    lock4tc ($$, \"LWAR\
NING\", \"LSET\", $msg);\n  }\n\nsub signal_cleanu\
p\n  {\n    print dtderr \"\\n**** $$ (tcg) was ki\
lled\\n\";\n    &cleanup;\n    exit ($EXIT_FAILURE\
);\n  }\nsub clean_dir\n  {\n    my $dir=@_[0];\n \
   if ( !-d $dir){return ;}\n    elsif (!($dir=~/t\
mp/)){return ;}#safety check 1\n    elsif (($dir=~\
/\\*/)){return ;}#safety check 2\n    else\n      \
{\n	`rm -rf $dir`;\n      }\n    return;\n  }\nsub\
 cleanup\n  {\n    #print stderr \"\\n----tc: $$ K\
ills $PIDCHILD\\n\";\n    #kill (SIGTERM,$PIDCHILD\
);\n    my $p=getppid();\n    $CLEAN_EXIT_STARTED=\
1;\n    \n    \n    \n    if (&lock4tc($$,\"LERROR\
\", \"LCHECK\", \"\"))\n      {\n	my $ppid=getppid\
();\n	if (!$ERROR_DONE) \n	  {\n	    &lock4tc($$,\\
"LERROR\", \"LSET\", \"$$ -- STACK: $p -> $$\\n\")\
;\n	    &lock4tc($$,\"LERROR\", \"LSET\", \"$$ -- \
COM: $CL\\n\");\n	  }\n      }\n    my $warning=&l\
ock4tc($$, \"LWARNING\", \"LREAD\", \"\");\n    my\
 $error=&lock4tc($$,  \"LERROR\", \"LREAD\", \"\")\
;\n    #release error and warning lock if root\n  \
  \n    if (isrootpid() && ($warning || $error) )\\
n      {\n	\n	print STDERR \"**************** Summ\
ary *************\\n$error\\n$warning\\n\";\n\n	&l\
ock4tc($$,\"LERROR\",\"RELEASE\",\"\");\n	&lock4tc\
($$,\"LWARNING\",\"RELEASE\",\"\");\n      } \n   \
 \n    \n    foreach my $f (@TMPFILE_LIST)\n      \
{\n	if (-e $f){unlink ($f);} \n      }\n    foreac\
h my $d (@TMPDIR_LIST)\n      {\n	clean_dir ($d);\\
n      }\n    #No More Lock Release\n    #&lock4tc\
($$,\"LLOCK\",\"LRELEASE\",\"\"); #release lock \n\
\n    if ( $debug_lock ){print STDERR \"\\n\\n\\n*\
********* END PG: $PROGRAM ($$) *************\\n\"\
;}\n    if ( $debug_lock ){print STDERR \"\\n\\n\\\
n**********(tcg) LOCKDIR: $LOCKDIR $$ ************\
*\\n\";}\n  }\nEND \n  {\n    \n    &cleanup();\n \
 }\n   \n\nsub safe_system \n{\n  my $com=shift;\n\
  my $ntry=shift;\n  my $ctry=shift;\n  my $pid;\n\
  my $status;\n  my $ppid=getppid();\n  if ($com e\
q \"\"){return 1;}\n  \n  \n\n  if (($pid = fork (\
)) < 0){return (-1);}\n  if ($pid == 0)\n    {\n  \
    set_lock($$, \" -SHELL- $com (tcg)\");\n      \
exec ($com);\n    }\n  else\n    {\n      lock4tc \
($$, \"LLOCK\", \"LSET\", \"$pid\\n\");#update par\
ent\n      $PIDCHILD=$pid;\n    }\n  if ($debug_lo\
ck){printf STDERR \"\\n\\t .... safe_system (fasta\
_seq2hmm)  p: $$ c: $pid COM: $com\\n\";}\n\n  wai\
tpid ($pid,WTERMSIG);\n\n  shift_lock ($pid,$$, \"\
LWARNING\",\"LWARNING\", \"LSET\");\n\n  if ($? ==\
 $EXIT_FAILURE || lock4tc($pid, \"LERROR\", \"LCHE\
CK\", \"\"))\n    {\n      if ($ntry && $ctry <$nt\
ry)\n	{\n	  add_warning ($$,$$,\"$com failed [retr\
y: $ctry]\");\n	  lock4tc ($pid, \"LRELEASE\", \"L\
ERROR\", \"\");\n	  return safe_system ($com, $ntr\
y, ++$ctry);\n	}\n      elsif ($ntry == -1)\n	{\n	\
  if (!shift_lock ($pid, $$, \"LERROR\", \"LWARNIN\
G\", \"LSET\"))\n	    {\n	      add_warning ($$,$$\
,\"$com failed\");\n	    }\n	  else\n	    {\n	    \
  lock4tc ($pid, \"LRELEASE\", \"LERROR\", \"\");\\
n	    }\n	  return $?;}\n      else\n	{\n	  if (!s\
hift_lock ($pid,$$, \"LERROR\",\"LERROR\", \"LSET\\
"))\n	    {\n	      myexit(add_error ($EXIT_FAILUR\
E,$$,$pid,getppid(), \"UNSPECIFIED system\", $com)\
);\n	    }\n	}\n    }\n  return $?;\n}\n\nsub chec\
k_configuration \n    {\n      my @l=@_;\n      my\
 $v;\n      foreach my $p (@l)\n	{\n	  \n	  if   (\
 $p eq \"EMAIL\")\n	    { \n	      if ( !($EMAIL=~\
/@/))\n		{\n		add_warning($$,$$,\"Could Not Use EM\
AIL\");\n		myexit(add_error ($EXIT_FAILURE,$$,$$,g\
etppid(),\"EMAIL\",\"$CL\"));\n	      }\n	    }\n	\
  elsif( $p eq \"INTERNET\")\n	    {\n	      if ( \
!&check_internet_connection())\n		{\n		  myexit(ad\
d_error ($EXIT_FAILURE,$$,$$,getppid(),\"INTERNET\\
",\"$CL\"));\n		}\n	    }\n	  elsif( $p eq \"wget\\
")\n	    {\n	      if (!&pg_is_installed (\"wget\"\
) && !&pg_is_installed (\"curl\"))\n		{\n		  myexi\
t(add_error ($EXIT_FAILURE,$$,$$,getppid(),\"PG_NO\
T_INSTALLED:wget\",\"$CL\"));\n		}\n	    }\n	  els\
if( !(&pg_is_installed ($p)))\n	    {\n	      myex\
it(add_error ($EXIT_FAILURE,$$,$$,getppid(),\"PG_N\
OT_INSTALLED:$p\",\"$CL\"));\n	    }\n	}\n      re\
turn 1;\n    }\nsub pg_is_installed\n  {\n    my @\
ml=@_;\n    my $r, $p, $m;\n    my $supported=0;\n\
    \n    my $p=shift (@ml);\n    if ($p=~/::/)\n \
     {\n	if (safe_system (\"perl -M$p -e 1\")==$EX\
IT_SUCCESS){return 1;}\n	else {return 0;}\n      }\
\n    else\n      {\n	$r=`which $p 2>/dev/null`;\n\
	if ($r eq \"\"){return 0;}\n	else {return 1;}\n  \
    }\n  }\n\n\n\nsub check_internet_connection\n \
 {\n    my $internet;\n    my $tmp;\n    &check_co\
nfiguration ( \"wget\"); \n    \n    $tmp=&vtmpnam\
 ();\n    \n    if     (&pg_is_installed    (\"wge\
t\")){`wget www.google.com -O$tmp >/dev/null 2>/de\
v/null`;}\n    elsif  (&pg_is_installed    (\"curl\
\")){`curl www.google.com -o$tmp >/dev/null 2>/dev\
/null`;}\n    \n    if ( !-e $tmp || -s $tmp < 10)\
{$internet=0;}\n    else {$internet=1;}\n    if (-\
e $tmp){unlink $tmp;}\n\n    return $internet;\n  \
}\nsub check_pg_is_installed\n  {\n    my @ml=@_;\\
n    my $r=&pg_is_installed (@ml);\n    if (!$r &&\
 $p=~/::/)\n      {\n	print STDERR \"\\nYou Must I\
nstall the perl package $p on your system.\\nRUN:\\
\n\\tsudo perl -MCPAN -e 'install $pg'\\n\";\n    \
  }\n    elsif (!$r)\n      {\n	myexit(flush_error\
(\"\\nProgram $p Supported but Not Installed on yo\
ur system\"));\n      }\n    else\n      {\n	retur\
n 1;\n      }\n  }\n\n\n","use Cwd;\nuse Env;\nuse\
 File::Path;\nuse FileHandle;\nuse strict;\n\n\nou\
r (%MODE, %PG, %ENV_SET, %SUPPORTED_OS);\n\n\nour \
$EXIT_SUCCESS=0;\nour $EXIT_FAILURE=1;\nour $INTER\
NET=0;\n\nour $CP=\"cp \"; #was causing a crash on\
 MacOSX\nour $SILENT=\">/dev/null 2>/dev/null\";\n\
our $WEB_BASE=\"http://www.tcoffee.org\";\nour $TC\
LINKDB_ADDRESS=\"$WEB_BASE/Resources/tclinkdb.txt\\
";\nour $OS=get_os();\nour $ROOT=&get_root();\nour\
 $CD=cwd();\nour $CDIR=$CD;\nour $HOME=$ENV{'HOME'\
};\n\nour $OSNAME=$ENV{'OSNAME'};\nour $OSARCH=$EN\
V{'OSARCH'};\nour $REPO_ROOT=\"\";\n\nour $TCDIR;\\
nour $TCCACHE;\nour $TCTMP;\nour $TCM;\nour $TCMET\
HODS;\nour $TCPLUGINS;\nour $PLUGINS_DIR=\"\";\nou\
r $INSTALL_DIR=\"\";\n\nour $CXX=\"g++\";\nour $CX\
XFLAGS=\"\";\n\nour $CPP=\"g++\";\nour $CPPFLAGS=\\
"\";\n\nour $CC=\"gcc\";\nour $CFLAGS=$ENV{'CFLAGS\
'};\n\nour $FC=\"f77\";\nour $FFLAGS=\"\";\n\nmy $\
install=\"all\";\nmy $default_update_action=\"no_u\
pdate\";\nmy @required_applications=(\"wget_OR_cur\
l\");\nmy @smode=(\"all\", \"clean\", \"install\")\
;\n\n&initialize_PG();\n\nmy $cl=join( \" \", @ARG\
V);\nif ($#ARGV==-1 || ($cl=~/-h/) ||($cl=~/-H/) )\
\n  {\n     print \"\\n!!!!!!! ./install  t_coffee\
             --> installs t_coffee only\";\n     p\
rint \"\\n!!!!!!! ./install  all                  \
--> installs all the modes [mcoffee, expresso, psi\
coffee,rcoffee..]\";\n     print \"\\n!!!!!!! ./in\
stall  [mcoffee|rcoffee|..] --> installs the speci\
fied mode\";\n     print \"\\n!!!!!!! ./install  -\
h                   --> print usage\\n\\n\";\n    \
 if ( $#ARGV==-1){exit ($EXIT_FAILURE);}\n   }\n  \
   \nif (($cl=~/-h/) ||($cl=~/-H/) )\n  {\n    my \
$m;\n    print \"\\n\\n!!!!!!! advanced mode\\n\";\
\n    foreach $m ((keys (%MODE)),@smode)\n      {\\
n	print \"!!!!!!!       ./install $m\\n\";\n      \
}\n    \n    print \"!!!!!!! ./install [target:pac\
kage|mode|] [-update|-force|-exec=dir|-dis=dir|-ro\
ot|-tclinkdb=file|-] [CC=|FCC=|CXX=|CFLAGS=|CXXFLA\
GS=]\\n\";\n    print \"!!!!!!! ./install clean   \
 [removes all executables]\\n\";\n    print \"!!!!\
!!! ./install [optional:target] -update           \
    [updates package already installed]\\n\";\n   \
 print \"!!!!!!! ./install [optional:target] -forc\
e                [Forces recompilation over everyt\
hing]\\n\";\n    \n    print \"!!!!!!! ./install [\
optional:target] -root                 [You are ru\
nning as root]\\n\";\n    print \"!!!!!!! ./instal\
l [optional:target] -exec=/foo/bar/       [address\
 for the T-Coffee executable]\\n\";\n    print \"!\
!!!!!! ./install [optional:target] -dis=/foo/bar/ \
       [Address where distributions should be stor\
ed]\\n\";\n    print \"!!!!!!! ./install [optional\
:target] -tclinkdb=foo|update  [file containing al\
l the packages to be installed]\\n\";\n    print \\
"!!!!!!! ./install [optional:target] -clean       \
         [clean everything]\\n\";\n    print \"!!!\
!!!! ./install [optional:target] -plugins         \
     [plugins directory]\\n\";\n    print \"!!!!!!\
! ./install [optional:target] -tcdir=/foor/bar    \
  [base path where T-Coffee will be installed]\\n\\
";\n    print \"!!!!!!! ./install [optional:target\
] -repo=/path/to/repo   [binaries repository root \
directory]\\n\";\n    print \"!!!!!!! mode:\";\n  \
  foreach $m (keys(%MODE)){print \"$m \";}\n    pr\
int \"\\n\";\n    print \"!!!!!!! Packages:\";\n  \
  foreach $m (keys (%PG)){print \"$m \";}\n    pri\
nt \"\\n\";\n    \n    print \"\\n\\n\";\n    exit\
 ($EXIT_FAILURE);\n  }\n\n\n\nmy (@argl)=($cl=~/(\\
\S+=[^=]+)\\s\\w+=/g);\npush (@argl, ($cl=~/(\\S+=\
[^=]+\\S)\\s*$/g));\n\nforeach $a (@argl)\n  {\n  \
  if ( ($cl=~/CXX=(.*)/)){$CXX=$1;}\n    if ( ($cl\
=~/-CC=(.*)/    )){$CC=$1;}\n    if ( ($cl=~/-FC=(\
.*)/    )){$FC=$1;}\n    if ( ($cl=~/-CFLAGS=(.*)/\
)){$CFLAGS=$1;}\n    if ( ($cl=~/-CXXFLAGS=(.*)/))\
{$CXXFLAGS=$1;}\n  }\nour ($ROOT_INSTALL, $NO_QUES\
TION, $default_update_action,$BINARIES_ONLY,$force\
, $default_update_action, $INSTALL_DIR, $PLUGINS_D\
IR, $DISTRIBUTIONS,$tclinkdb, $proxy, $clean);\nif\
 ( ($cl=~/-root/)){$ROOT_INSTALL=1;}\nif ( ($cl=~/\
-no_question/)){$NO_QUESTION=1;}\nif ( ($cl=~/-upd\
ate/)){$default_update_action=\"update\";}\nif ( (\
$cl=~/-binaries/)){$BINARIES_ONLY=1;}\nif ( ($cl=~\
/-force/)){$force=1;$default_update_action=\"updat\
e\"}\nif ( ($cl=~/-exec=\\s*(\\S+)/)){$INSTALL_DIR\
=$1;}\nif ( ($cl=~/-plugins=\\s*(\\S+)/)){$PLUGINS\
_DIR=$1;}\nif ( ($cl=~/-dis=\\s*(\\S+)/)){$DISTRIB\
UTIONS=$1;}\n\nif ( ($cl=~/-tclinkdb=\\s*(\\S+)/))\
{$tclinkdb=$1;}\nif ( ($cl=~/-proxy=\\s*(\\S+)/)){\
$proxy=$1;}\nif ( ($cl=~/-clean/)){$clean=1;}\nif \
( ($cl=~/-repo=\\s*(\\S+)/)){ $REPO_ROOT=$1; }\nif\
 ( ($cl=~/-tcdir=\\s*(\\S+)/)){ $TCDIR=$1; }\nif (\
$tclinkdb){&update_tclinkdb ($tclinkdb);}\n\n\nif(\
 $REPO_ROOT ne \"\" ) {\n	if( $OSNAME eq \"\" ) { \
print \"You have specified the repository folder b\
ut the required \\\"OSNAME\\\" enviroment variable\
 is missing. \\n\"; exit 1; } \n	if( $OSARCH eq \"\
\" ) { print \"You have specified the repository f\
older but the required \\\"OSARCH\\\" enviroment v\
ariable is missing. \\n\"; exit 1; } \n}\n\n\nif(!\
$TCDIR) { $TCDIR=\"$HOME/.t_coffee\"; }\n&add_dir \
($TCDIR);\n&add_dir ($TCCACHE=\"$TCDIR/cache\");\n\
&add_dir ($TCTMP=\"$CDIR/tmp\");\n&add_dir ($TCM=\\
"$TCDIR/mcoffee\");\n&add_dir ($TCMETHODS=\"$TCDIR\
/methods\");\n&add_dir ($TCPLUGINS=\"$TCDIR/plugin\
s/$OS\");\n\n\nour $BASE=\"$CD/bin\";\nour $BIN=\"\
$BASE/binaries/$OS\";\nour $DOWNLOAD_DIR=\"$BASE/d\
ownload\";\nour $DOWNLOAD_FILE=\"$DOWNLOAD_DIR/fil\
es\";\nour $TMP=\"$BASE/tmp\";\n\n&add_dir($BASE);\
\n&add_dir($BIN);\n&add_dir($DOWNLOAD_DIR);\n&add_\
dir($DOWNLOAD_FILE);\nif (!$DISTRIBUTIONS){$DISTRI\
BUTIONS=\"$DOWNLOAD_DIR/distributions\";}\n&add_di\
r ($DISTRIBUTIONS);\n&add_dir ($TMP);\n\n\nif    (\
!$PLUGINS_DIR && !$ROOT_INSTALL){$PLUGINS_DIR=$TCP\
LUGINS;}\nelsif (!$PLUGINS_DIR &&  $ROOT_INSTALL){\
$PLUGINS_DIR=\"/usr/local/bin/\";}\n\nif    (!$INS\
TALL_DIR && !$ROOT_INSTALL){$INSTALL_DIR=\"$HOME/b\
in/\";mkpath ($INSTALL_DIR);}\nelsif (!$INSTALL_DI\
R &&  $ROOT_INSTALL){$INSTALL_DIR=\"/usr/local/bin\
/\";}\n\nif (-d \"mcoffee\"){`cp mcoffee/* $TCM`;}\
\n\n\nour $ENV_FILE=\"$TCDIR/t_coffee_env\";\n&env\
_file2putenv ($ENV_FILE);\n&set_proxy($proxy);\nmy\
 ($target, $p, $r);\n$target=$p;\n\nforeach $p (  \
((keys (%PG)),(keys(%MODE)),(@smode)) )\n  {\n    \
if ($ARGV[0] eq $p && $target eq \"\"){$target=$p;\
}\n  }\nif ($target eq \"\"){exit ($EXIT_FAILURE);\
}\n\n\nforeach $r (@required_applications)\n  {\n \
   my @app_list;\n    my $i;\n    $i=0;\n    \n   \
 @app_list=split (/_OR_/, $r);\n    foreach my $pg\
 (@app_list)\n      {\n	$i+=&pg_is_installed ($pg)\
;\n      }\n    if ($i==0)\n      {\n      print \\
"One of the following packages must be installed t\
o proceed: \";\n      foreach my $pg (@app_list)\n\
	{\n	  print (\"$pg \");\n	}\n      die;\n    }\n \
 }\n\n\n\n\n\n\n&sign_license_ni();\n\n\n$PG{C}{co\
mpiler}=get_C_compiler($CC);\n$PG{Fortran}{compile\
r}=get_F_compiler($FC);\n$PG{CXX}{compiler}=$PG{CP\
P}{compiler}=$PG{GPP}{compiler}=get_CXX_compiler($\
CXX);\nif ($CXXFLAGS){$PG{CPP}{options}=$PG{GPP}{o\
ptions}=$PG{CXX}{options}=$CXXFLAGS;}\nif ($CFLAGS\
 ne \"\" ){$PG{C}{options}=$CFLAGS;}\nforeach my $\
c (keys(%PG))\n  {\n    my $arguments;\n    if ($P\
G{$c}{compiler})\n      {\n	$arguments=\"$PG{$c}{c\
ompiler_flag}=$PG{$c}{compiler} \";\n	if ($PG{$c}{\
options})\n	  {\n	    $arguments.=\"$PG{$c}{option\
s_flag}='\" . $PG{$c}{options} . \"' \";\n	  }\n	$\
PG{$c}{arguments}=$arguments;\n      }\n  }\n\nif \
($PG{$target}){$PG{$target}{install}=1;}\nelse\n  \
{\n    foreach my $pg (keys(%PG))\n      {\n	if ( \
$target eq \"all\" || ($PG{$pg}{mode}=~/$target/))\
\n	  {\n	    $PG{$pg} {install}=1;\n	  }\n      }\\
n  }\n\nforeach my $pg (keys(%PG))\n  {\n    if (!\
$PG{$pg}{update_action}){$PG{$pg}{update_action}=$\
default_update_action;}\n    elsif ($PG{$pg}{updat\
e_action} eq \"never\"){$PG{$pg}{install}=0;}\n   \
 if ( $force && $PG{$pg}{install})\n      {\n	`rm \
$BIN/$pg $BIN/$pg.exe $SILENT`;\n      }\n    if (\
$PG{$pg}{update_action} eq \"update\" && $PG{$pg}{\
install}){$PG{$pg}{update}=1;}\n  }\n\nif (($targe\
t=~/clean/))\n  {\n    print \"------- cleaning ex\
ecutables -----\\n\";\n    `rm bin/* $SILENT`;\n  \
  exit ($EXIT_SUCCESS);\n  }\n\nif ( !$PG{$target}\
){print \"------- Installing T-Coffee Modes\\n\";}\
\n\nforeach my $m (keys(%MODE))\n  {\n    if ( $ta\
rget eq \"all\" || $target eq $m)\n      {\n	print\
 \"\\n------- The installer will now install the $\
m components $MODE{$m}{description}\\n\";\n	foreac\
h my $pg (keys(%PG))\n	  {\n	    if ( $PG{$pg}{mod\
e} =~/$m/ && $PG{$pg}{install})\n	      {\n		if ($\
PG{$pg}{touched}){print \"------- $PG{$pg}{dname}:\
 already processed\\n\";}\n		else {$PG{$pg}{succes\
s}=&install_pg($pg);$PG{$pg}{touched}=1;}\n	      \
}\n	  }\n      }\n  }\n\nif ( $PG{$target}){print \
\"------- Installing Individual Package\\n\";}\nfo\
reach my $pg (keys (%PG))\n  {\n    \n    if ( $PG\
{$pg}{install} && !$PG{$pg}{touched})\n      {\n	p\
rint \"\\n------- Install $pg\\n\";\n	$PG{$pg}{suc\
cess}=&install_pg($pg);$PG{$pg}{touched}=1;\n     \
 }\n  }\nprint \"------- Finishing The installatio\
n\\n\";\nmy $final_report=&install ($INSTALL_DIR);\
\n\nprint \"\\n\";\nprint \"**********************\
***********************************************\\n\
\";\nprint \"********              INSTALLATION SU\
MMARY          *****************\\n\";\nprint \"**\
**************************************************\
*****************\\n\";\nprint \"------- SUMMARY p\
ackage Installation:\\n\";\nprint \"-------   Exec\
utable Installed in: $PLUGINS_DIR\\n\";\n\nforeach\
 my $pg (keys(%PG))\n  {\n    if ( $PG{$pg}{instal\
l})\n      {\n	my $bin_status=($PG{$pg}{from_binar\
y} && $PG{$pg}{success})?\"[from binary]\":\"\";\n\
	if     ( $PG{$pg}{new} && !$PG{$pg}{old})        \
             {print \"*------        $PG{$pg}{dnam\
e}: installed $bin_status\\n\"; $PG{$pg}{status}=1\
;}\n	elsif  ( $PG{$pg}{new} &&  $PG{$pg}{old})    \
                 {print \"*------        $PG{$pg}{\
dname}: updated $bin_status\\n\"  ; $PG{$pg}{statu\
s}=1;} \n	elsif  (!$PG{$pg}{new} &&  $PG{$pg}{old}\
 && !$PG{$pg}{update}){print \"*------        $PG{\
$pg}{dname}: previous\\n\" ; $PG{$pg}{status}=1;}\\
n	elsif  (!$PG{$pg}{new} &&  $PG{$pg}{old} &&  $PG\
{$pg}{update}){print \"*------        $PG{$pg}{dna\
me}: failed update (previous installation availabl\
e)\\n\";$PG{$pg}{status}=0;}\n	else               \
                                           {print \
\"*------        $PG{$pg}{dname}: failed installat\
ion\\n\";$PG{$pg}{status}=0;}\n      }\n  }\nmy $f\
ailure;\n\nif ( !$PG{$target}){print \"*------ SUM\
MARY mode Installation:\\n\";}\nforeach my $m (key\
s(%MODE))\n  {\n  \n    if ( $target eq \"all\" ||\
 $target eq $m)\n      {\n	my $succesful=1;\n	fore\
ach my $pg (keys(%PG))\n	  {\n	    if (($PG{$pg}{m\
ode}=~/$m/) && $PG{$pg}{install} && $PG{$pg}{statu\
s}==0)\n	      {\n		$succesful=0;\n		print \"*!!!!\
!!       $PG{$pg}{dname}: Missing\\n\";\n	      }\\
n	  }\n	if ( $succesful)\n	  {\n	    $MODE{$m}{sta\
tus}=1;\n	    print \"*------       MODE $MODE{$m}\
{dname} SUCCESSFULLY installed\\n\";\n	  }\n	else\\
n	  {\n	    $failure++;\n	    $MODE{$m}{status}=0;\
\n	    print \"*!!!!!!       MODE $MODE{$m}{dname}\
 UNSUCCESSFULLY installed\\n\";\n	  }\n      }\n  \
}\n\n    \n      \nif ($clean==1 && ($BASE=~/insta\
ll4tcoffee/) ){print \"*------ Clean Installation \
Directory: $BASE\\n\";`rm -rf $BASE`;}\nforeach my\
 $pg (keys(%PG)){if ($PG{$pg}{install} && $PG{$pg}\
{status}==0){exit ($EXIT_FAILURE);}}\n\nif ($failu\
re)\n  {\n    print \"****************************\
*****************************************\\n\";\n \
   print \"********     SOME PACKAGES FAILED TO IN\
STALL        *****************\\n\";\n    print \"\
**************************************************\
*******************\\n\";\n    print \"\\nSome of \
the reported failures may be due to connectivity p\
roblems\";\n    print \"\\nRerun the installation \
and the installer will specifically try to install\
 the missing packages\";\n    print \"\\nIf this F\
ails, go to the original website and install the p\
ackage manually\";\n  }\n\nprint \"***************\
**************************************************\
****\\n\";\nprint \"********              FINALIZE\
 YOUR INSTALLATION    *****************\\n\";\npri\
nt \"*********************************************\
************************\\n\";\nprint \"------- Yo\
ur executables are in:\\n\"; \nprint \"-------    \
   $PLUGINS_DIR:\\n\";\nprint \"------- Add this d\
irectory to your path with the following command:\\
\n\";\nprint \"-------       export PATH=$PLUGINS_\
DIR:\\$PATH\\n\";\nprint \"------- Make this perma\
nent by adding this line to the file:\\n\";\nprint\
 \"-------       $HOME/.bashrc\\n\";\nexit ($EXIT_\
SUCCESS);  \n  \nsub get_CXX_compiler\n  {\n    my\
 $c=@_[0];\n    my (@clist)=(\"g++\");\n    \n    \
return get_compil ($c, @clist);\n }\nsub get_C_com\
piler\n  {\n    my $c=@_[0];\n    my (@clist)=(\"g\
cc\", \"cc\", \"icc\");\n    \n    return get_comp\
il ($c, @clist);\n }\n\nsub get_F_compiler\n  {\n \
   my ($c)=@_[0];\n    my @clist=(\"f77\", \"g77\"\
,\"g95\", \"gfortran\", \"ifort\");\n    return ge\
t_compil ($c, @clist);\n  } \n       \nsub get_com\
pil\n  {\n    my ($fav,@clist)=(@_);\n    \n    #r\
eturn the first compiler found installed in the sy\
stem. Check first the favorite\n    foreach my $c \
($fav,@clist)\n      {\n	if  (&pg_is_installed ($c\
)){return $c;}\n      }\n    return \"\";\n  }\nsu\
b exit_if_pg_not_installed\n  {\n    my (@arg)=(@_\
);\n    \n    foreach my $p (@arg)\n      {\n	if (\
 !&pg_is_installed ($p))\n	  {\n	    print \"!!!!!\
!!! The $p utility must be installed for this inst\
allation to proceed [FATAL]\\n\";\n	    die;\n	  }\
\n      }\n    return 1;\n  }\nsub set_proxy\n  {\\
n    my ($proxy)=(@_);\n    my (@list,$p);\n    \n\
    @list= (\"HTTP_proxy\", \"http_proxy\", \"HTTP\
_PROXY\", \"ALL_proxy\", \"all_proxy\",\"HTTP_prox\
y_4_TCOFFEE\",\"http_proxy_4_TCOFFEE\");\n    \n  \
  if (!$proxy)\n      {\n	foreach my $p (@list)\n	\
  {\n	    if ( ($ENV_SET{$p}) || $ENV{$p}){$proxy=\
$ENV{$p};}\n	  }\n      }\n    foreach my $p(@list\
){$ENV{$p}=$proxy;}\n  }\n	\nsub check_internet_co\
nnection\n  {\n    my $internet;\n    \n    if ( -\
e \"x\"){unlink (\"x\");}\n    if     (&pg_is_inst\
alled    (\"wget\")){`wget www.google.com -Ox >/de\
v/null 2>/dev/null`;}\n    elsif  (&pg_is_installe\
d    (\"curl\")){`curl www.google.com -ox >/dev/nu\
ll 2>/dev/null`;}\n    else\n      {\n	printf stde\
rr \"\\nERROR: No pg for remote file fetching [wge\
t or curl][FATAL]\\n\";\n	exit ($EXIT_FAILURE);\n \
     }\n    \n    if ( !-e \"x\" || -s \"x\" < 10)\
{$internet=0;}\n    else {$internet=1;}\n    if (-\
e \"x\"){unlink \"x\";}\n    return $internet;\n  \
}\nsub url2file\n  {\n    my ($cmd, $file,$wget_ar\
g, $curl_arg)=(@_);\n    my ($exit,$flag, $pg, $ar\
g);\n    \n    if ($INTERNET || check_internet_con\
nection ()){$INTERNET=1;}\n    else\n      {\n	pri\
nt STDERR \"ERROR: No Internet Connection [FATAL:i\
nstall.pl]\\n\";\n	exit ($EXIT_FAILURE);\n      }\\
n    \n    if     (&pg_is_installed    (\"wget\"))\
{$pg=\"wget\"; $flag=\"-O\";$arg=\"--tries=2 --con\
nect-timeout=10 $wget_arg\";}\n    elsif  (&pg_is_\
installed    (\"curl\")){$pg=\"curl\"; $flag=\"-o\\
";$arg=$curl_arg;}\n    else\n      {\n	printf std\
err \"\\nERROR: No pg for remote file fetching [wg\
et or curl][FATAL]\\n\";\n	exit ($EXIT_FAILURE);\n\
      }\n    \n    \n    if (-e $file){unlink($fil\
e);}\n    $exit=system \"$pg $cmd $flag$file $arg\\
";\n    return $exit;\n  }\n\nsub pg_is_installed\\
n  {\n    my ($p, $dir)=(@_);\n    my ($r,$m, $ret\
);\n    my ($supported, $language, $compil);\n    \
\n  \n    if ( $PG{$p})\n      {\n	$language=$PG{$\
p}{language2};\n	$compil=$PG{$language}{compiler};\
\n      }\n    \n    if ( $compil eq \"CPAN\")\n  \
    {\n	if ( system (\"perl -M$p -e 1\")==$EXIT_SU\
CCESS){$ret=1;}\n	else {$ret=0;}\n      }\n    els\
if ($dir)\n      {\n	if (-e \"$dir/$p\" || -e \"$d\
ir/$p\\.exe\"){$ret=1;}\n	else {$ret=0;}\n      }\\
n    elsif (-e \"$PLUGINS_DIR/$p\" || -e \"$PLUGIN\
S_DIR/$p.exe\"){$ret=1;}\n    else\n      {\n	$r=`\
which $p 2>/dev/null`;\n	if ($r eq \"\"){$ret=0;}\\
n	else {$ret=1;}\n      }\n   \n    return $ret;\n\
  }\nsub install\n  {\n    my ($new_bin)=(@_);\n  \
  my ($copied, $report);\n\n    \n    if (!$ROOT_I\
NSTALL)\n      {\n	\n	if (-e \"$BIN/t_coffee\"){`$\
CP $BIN/t_coffee $INSTALL_DIR`};\n	`cp $BIN/* $PLU\
GINS_DIR`;\n	$copied=1;\n      }\n    else\n      \
{\n	$copied=&root_run (\"You must be root to final\
ize the installation\", \"$CP $BIN/* $INSTALL_DIR \
$SILENT\");\n      }\n    \n     \n  if ( !$copied\
)\n    {\n      $report=\"*!!!!!! Installation uns\
uccesful. The executables have been left in $BASE/\
bin\\n\";\n    }\n  elsif ( $copied && $ROOT)\n   \
 {\n      $report=\"*------ Installation succesful\
. Your executables have been copied in $new_bin an\
d are on your PATH\\n\";\n    }\n  elsif ( $copied\
 && !$ROOT)\n    {\n      $report= \"*!!!!!! T-Cof\
fee and associated packages have been copied in: $\
new_bin\\n\";\n      $report.=\"*!!!!!! This addre\
ss is NOT in your PATH sytem variable\\n\";\n     \
 $report.=\"*!!!!!! You can do so by adding the fo\
llowing line in your ~/.bashrc file:\\n\";\n      \
$report.=\"*!!!!!! export PATH=$new_bin:\\$PATH\\n\
\";\n    }\n  return $report;\n}\n\nsub sign_licen\
se_ni\n  {\n    my $F=new FileHandle;\n    open ($\
F, \"license.txt\");\n    while (<$F>)\n      {\n	\
print \"$_\";\n      }\n    close ($F);\n    \n   \
 return;\n  }\n\nsub install_pg\n  {\n    my ($pg)\
=(@_);\n    my ($report, $previous, $language, $co\
mpiler, $return);\n    \n    if (!$PG{$pg}{install\
}){return 1;}\n    \n    $previous=&pg_is_installe\
d ($pg);\n    \n    if ($PG{$pg}{update_action} eq\
 \"no_update\" && $previous)\n      {\n	$PG{$pg}{o\
ld}=1;\n	$PG{$pg}{new}=0;\n	$return=1;\n      }\n \
   else\n      {\n	$PG{$pg}{old}=$previous;\n	\n	i\
f ($PG{$pg} {language2} eq \"Perl\"){&install_perl\
_package ($pg);}\n	elsif ($BINARIES_ONLY && &insta\
ll_binary_package ($pg)){$PG{$pg}{from_binary}=1;}\
\n	elsif (&install_source_package ($pg)){;}\n	else\
 \n	  {\n	    \n	    if (!&supported_os($OS))\n	  \
    {\n		print \"!!!!!!!! $pg compilation failed, \
binary unsupported for $OS\\n\"; \n	      }\n	    \
elsif (!($PG{$pg}{from_binary}=&install_binary_pac\
kage ($pg)))\n	      {\n		print \"!!!!!!!! $pg com\
pilation and  binary installation failed\\n\";\n	 \
     }\n	  }\n	$PG{$pg}{new}=$return=&pg_is_instal\
led ($pg,$BIN);\n      }\n\n    \n    return $retu\
rn;\n  }\nsub install_perl_package\n  {\n    my ($\
pg)=(@_);\n    my ($report, $language, $compiler);\
\n    \n    $language=$PG{$pg} {language2};\n    $\
compiler=$PG{$language}{compiler};\n    \n    if (\
!&pg_is_installed ($pg))\n      {\n	if ( $OS eq \"\
windows\"){`perl -M$compiler -e 'install $pg'`;}\n\
	elsif ( $ROOT eq \"sudo\"){system (\"sudo perl -M\
$compiler -e 'install $pg'\");}\n	else {system (\"\
su root -c perl -M$compiler -e 'install $pg'\");}\\
n      }\n    return &pg_is_installed ($pg);\n  }\\
n\n\n\nsub install_source_package\n  {\n    my ($p\
g)=(@_);\n    my ($report, $download, $arguments, \
$language, $address, $name, $ext, $main_dir, $dist\
rib);\n    my $wget_tmp=\"$TMP/wget.tmp\";\n    my\
 (@fl);\n    if ( -e \"$BIN/$pg\" || -e \"$BIN/$pg\
.exe\"){return 1;}\n    \n    #\n    # check if th\
e module exists in the repository cache \n    #\n	\
if( repo_load($pg) ) {\n		return 1;\n	}\n    \n   \
 if ($pg eq \"t_coffee\")  {return   &install_t_co\
ffee ($pg);}\n    elsif ($pg eq \"TMalign\"){retur\
n   &install_TMalign ($pg);}\n    \n    chdir $DIS\
TRIBUTIONS;\n    \n    $download=$PG{$pg}{source};\
\n    \n    if (($download =~/tgz/))\n      {\n	($\
address,$name,$ext)=($download=~/(.+\\/)([^\\/]+)(\
\\.tgz).*/);\n      }\n    elsif (($download=~/tar\
\\.gz/))\n      {\n	($address,$name,$ext)=($downlo\
ad=~/(.+\\/)([^\\/]+)(\\.tar\\.gz).*/);\n      }\n\
    elsif (($download=~/tar/))\n      {\n	($addres\
s,$name,$ext)=($download=~/(.+\\/)([^\\/]+)(\\.tar\
).*/);\n      }\n    else\n      {\n	($address,$na\
me)=($download=~/(.+\\/)([^\\/]+)/);\n	$ext=\"\";\\
n      }\n    $distrib=\"$name$ext\";\n    \n    i\
f ( !-d $pg){mkdir $pg;}\n    chdir $pg;\n   \n   \
 #get the distribution if available\n    if ( -e \\
"$DOWNLOAD_DIR/$distrib\")\n      {\n	`$CP $DOWNLO\
AD_DIR/$distrib .`;\n      }\n    #UNTAR and Prepa\
re everything\n    if (!-e \"$name.tar\" && !-e \"\
$name\")\n      {\n	&check_rm ($wget_tmp);\n	print\
 \"\\n------- Downloading/Installing $pg\\n\";\n	\\
n	if (!-e $distrib && &url2file (\"$download\", \"\
$wget_tmp\")==$EXIT_SUCCESS)\n	  {\n	    \n	    `m\
v $wget_tmp $distrib`;\n	    `$CP $distrib $DOWNLO\
AD_DIR/`;\n	  }\n\n	if (!-e $distrib)\n	  {\n	    \
print \"!!!!!!! Download of $pg distribution faile\
d\\n\";\n	    print \"!!!!!!! Check Address: $PG{$\
pg}{source}\\n\";\n	    return 0;\n	  }\n	print \"\
\\n------- unzipping/untaring $name\\n\";\n	if (($\
ext =~/z/))\n	  { \n	    &flush_command (\"gunzip \
$name$ext\");\n	    \n	  }\n	if (($ext =~/tar/) ||\
 ($ext =~/tgz/))\n	  {\n	    &flush_command(\"tar \
-xvf $name.tar\");\n	  }\n      }\n    #Guess and \
enter the distribution directory\n    @fl=ls($p);\\
n    foreach my $f (@fl)\n      {\n	if (-d $f)\n	 \
 {\n	    $main_dir=$f;\n	  }\n      }\n    if (-d \
$main_dir)\n	  \n      {\n	chdir $main_dir;}\n    \
else\n      {\n	print \"Error: $main_dir does not \
exist\";\n      }\n    print \"\\n------- Compilin\
g/Installing $pg\\n\";\n    `make clean $SILENT`;\\
n    \n    \n    #\n    # SAP module\n    #\n    i\
f ($pg eq \"sap\")\n      {\n	if (-e \"./configure\
\")\n	  {\n	    #new sap distribution\n	    \n	   \
 &flush_command (\"./configure\");\n	    &flush_co\
mmand (\"make clean\");\n	    &flush_command (\"ma\
ke\");\n	    &check_cp (\"./src/$pg\", \"$BIN\");\\
n	    repo_store(\"./src/$pg\");\n	  }\n	else\n	  \
{\n	    #old style distribution\n	    `rm *.o sap \
 sap.exe ./util/aa/*.o  ./util/wt/.o $SILENT`;\n	 \
   &flush_command (\"make $arguments sap\");\n	   \
 &check_cp ($pg, \"$BIN\");\n	    repo_store($pg);\
\n	  }\n      }\n    \n    #\n    # CLUSTALW2 modu\
le\n    #\n    elsif ($pg eq \"clustalw2\")\n     \
 {\n	&flush_command(\"./configure\");\n	&flush_com\
mand(\"make $arguments\");\n	&check_cp (\"./src/$p\
g\", \"$BIN\");\n	repo_store(\"./src/$pg\");\n    \
  }\n\n    #\n    # CLUSTAL-OMEGA module\n    #\n \
   elsif ($pg eq \"clustalo\")\n      {\n	&flush_c\
ommand(\"./configure\");\n	&flush_command(\"make $\
arguments\");\n	&check_cp (\"./src/$pg\", \"$BIN\"\
);\n	repo_store(\"./src/$pg\");\n      }\n\n    #\\
n    # STRIKE module\n    #\n    elsif ($pg eq \"s\
trike\")\n      {\n	&flush_command(\"make $argumen\
ts\");\n	&check_cp (\"./bin/$pg\", \"$BIN\");\n	re\
po_store(\"./bin/$pg\");\n      }\n    \n    #\n  \
  # FSA module\n    # \n    elsif ($pg eq \"fsa\")\
\n      {\n	&flush_command(\"./configure --prefix=\
$BIN\");\n	&flush_command(\"make $arguments\");\n	\
&flush_command (\"make install\");\n\n	repo_store(\
\"fsa\", \"$BIN/bin\");\n	`mv $BIN/bin/* $BIN`;\n	\
`rmdir $BIN/bin`;\n      }\n    \n    #\n    # CLU\
STALW module\n    #\n    elsif ($pg eq \"clustalw\\
")\n      {\n	&flush_command(\"make $arguments clu\
stalw\");\n	`$CP $pg $BIN $SILENT`;\n	repo_store($\
pg);\n      }\n    \n    #\n    # MAFFT module\n  \
  #\n    elsif ($pg eq \"mafft\")\n      {\n	my $b\
ase=cwd();\n	my $c;\n	\n	#compile core\n	mkpath (\\
"./mafft/bin\");\n	mkpath (\"./mafft/lib\");\n	chd\
ir \"$base/core\";\n	`make clean $SILENT`;\n	&flus\
h_command (\"make $arguments\");\n	&flush_command \
(\"make install LIBDIR=../mafft/lib BINDIR=../maff\
t/bin\");\n	\n	#compile extension\n	chdir \"$base/\
extensions\";\n	`make clean $SILENT`;\n	&flush_com\
mand (\"make $arguments\");\n	&flush_command (\"ma\
ke install LIBDIR=../mafft/lib BINDIR=../mafft/bin\
\");\n	\n	#put everything in mafft and copy the co\
mpiled stuff in bin\n	chdir \"$base\";\n	if ($ROOT\
_INSTALL)\n	  {\n	    &root_run (\"You Must be Roo\
t to Install MAFFT\\n\", \"mkdir /usr/local/mafft/\
;$CP mafft/lib/* /usr/local/mafft;$CP mafft/lib/ma\
fft* /usr/local/bin ;$CP mafft/bin/mafft /usr/loca\
l/bin/; \");\n	  }\n	else\n	  {\n	    `$CP mafft/l\
ib/*  $BIN`;\n	    `$CP mafft/bin/mafft  $BIN`;\n	\
  }\n	`tar -cvf mafft.tar mafft`;\n	`gzip mafft.ta\
r`;\n	`mv mafft.tar.gz $BIN`;\n	\n	repo_store(\"ma\
fft/bin/mafft\", \"mafft/lib/\", \"$BIN/mafft.tar.\
gz\");\n      }\n      \n    #\n    # DIALIGN-TX m\
odule\n    #\n    elsif ( $pg eq \"dialign-tx\" )\\
n      {\n	my $f;\n	my $base=cwd();\n\n	chdir \"./\
source\";\n	if ($OS eq \"macosx\"){&flush_command \
(\"cp makefile.MAC_OS makefile\");}\n\n	&flush_com\
mand (\" make CPPFLAGS='-O3 -funroll-loops' all\")\
;\n	\n	chdir \"..\";\n	&check_cp (\"./source/$pg\"\
, \"$BIN\");\n	repo_store(\"./source/$pg\");\n    \
  }\n      \n    #\n    # DIALIGN-T module \n    #\
 (is the same as dialign-tx, but it is mantained f\
or backward name compatibility with tcoffee)\n    \
#\n    elsif ( $pg eq \"dialign-t\" )\n      {\n	m\
y $f;\n	my $base=cwd();\n\n	chdir \"./source\";\n	\
if ($OS eq \"macosx\"){&flush_command (\"cp makefi\
le.MAC_OS makefile\");}\n\n	&flush_command (\" mak\
e CPPFLAGS='-O3 -funroll-loops' all\");\n	\n	chdir\
 \"..\";\n	&check_cp (\"./source/dialign-tx\", \"$\
BIN/dialign-t\");\n	repo_store(\"$BIN/dialign-t\")\
;	\n      }      \n      \n    #\n    # POA module\
\n    #\n    elsif ($pg eq \"poa\")\n      {\n	&fl\
ush_command (\"make $arguments poa\");\n	&check_cp\
 (\"$pg\", \"$BIN\");\n	repo_store(\"$pg\");\n    \
  }\n     \n     \n    #\n    # PROBCONS module\n \
   #\n    elsif ( $pg eq \"probcons\")\n      {\n	\
&add_C_libraries(\"./ProbabilisticModel.h\", \"lis\
t\", \"cstring\");\n	\n	`rm *.exe $SILENT`;\n	&flu\
sh_command (\"make $arguments probcons\");\n	&chec\
k_cp(\"$pg\", \"$BIN/$pg\");\n	repo_store(\"$pg\")\
;\n      }\n      \n    #\n    # PROBCONS RNA modu\
le\n    #\n    elsif ( $pg eq \"probconsRNA\")\n  \
    {\n	&add_C_libraries(\"./ProbabilisticModel.h\\
", \"list\", \"cstring\");\n	&add_C_libraries(\"./\
Main.cc\", \"iomanip\", \"cstring\",\"climits\");\\
n	`rm *.exe $SILENT`;\n	&flush_command (\"make $ar\
guments probcons\");\n	&check_cp(\"probcons\", \"$\
BIN/$pg\");\n	repo_store(\"$BIN/$pg\");\n      }\n\
\n	#\n	# MUSCLE module\n	#\n    elsif (  $pg eq \"\
muscle\")\n      {	\n	`rm *.o muscle muscle.exe $S\
ILENT`;\n	if ($OS eq \"macosx\" || $OS eq \"linux\\
")\n	  {\n	    &replace_line_in_file (\"./Makefile\
\", \"LDLIBS = -lm -static\",  \"LDLIBS = -lm\");\\
n	  }\n	elsif ($OS eq \"windows\")\n	  {\n	    &re\
place_line_in_file (\"./intmath.cpp\",  \"double l\
og2e\",      \"double cedric_log\");\n	    &replac\
e_line_in_file (\"./intmath.cpp\",  \"double log2\\
",       \"double log_notuse\");\n	    &replace_li\
ne_in_file (\"./intmath.cpp\",  \"double cedric_lo\
g\", \"double log2e\");\n	  }\n	&flush_command (\"\
make $arguments all\");\n	&check_cp(\"$pg\", \"$BI\
N\");\n	repo_store(\"$pg\");	\n      }\n      \n  \
   #\n     # MUS4 module\n     #\n     elsif (  $p\
g eq \"mus4\")\n      {\n	`rm *.o muscle muscle.ex\
e $SILENT`;\n	&flush_command (\"./mk\");\n	&check_\
cp(\"$pg\", \"$BIN\");\n	repo_store(\"$pg\");	\n  \
    }\n      \n    #\n    # PCMA module\n    #\n  \
  elsif ( $pg eq \"pcma\")\n      {\n	if ($OS eq \\
"macosx\")\n	  {\n	    &replace_line_in_file (\"./\
alcomp2.c\", \"malloc.h\",  \"\");\n	  }\n	&flush_\
command (\"make $arguments pcma\");\n	&check_cp(\"\
$pg\", \"$BIN\");\n	repo_store(\"$pg\");	\n      }\
\n      \n    #\n    # KALIGN module\n    #\n    e\
lsif ($pg eq \"kalign\")\n      {\n	&flush_command\
 (\"./configure\");\n	&flush_command(\"make $argum\
ents\");\n	&check_cp (\"$pg\",$BIN);\n	repo_store(\
\"$pg\");	\n      }\n      \n    #\n    # AMAP mod\
ule\n    #\n    elsif ( $pg eq \"amap\")\n      {\\
n	&add_C_libraries(\"./Amap.cc\", \"iomanip\", \"c\
string\",\"climits\");	\n	`make clean $SILENT`;\n	\
&flush_command (\"make $arguments all\");\n	&check\
_cp (\"$pg\", $BIN);\n	repo_store(\"$pg\");	\n    \
  }\n      \n    #\n    # PRODA module\n    #\n   \
 elsif ( $pg eq \"proda\")\n      {\n	&add_C_libra\
ries(\"AlignedFragment.h\", \"vector\", \"iostream\
\", \"cstring\",\"cstdlib\");\n	&add_C_libraries(\\
"Main.cc\", \"vector\", \"climits\");	\n	&add_C_li\
braries(\"Sequence.cc\", \"stdlib.h\", \"cstdio\")\
;	\n	&flush_command (\"make $arguments all\");\n	&\
check_cp (\"$pg\", $BIN);\n	repo_store(\"$pg\");	\\
n      }\n      \n    #\n    # PRANK module\n    #\
\n    elsif ( $pg eq \"prank\")\n      {\n	&flush_\
command (\"make $arguments all\");\n	&check_cp (\"\
$pg\", $BIN);\n	repo_store(\"$pg\");	\n      }\n  \
    \n    #\n    # !!!! MUSTANG module\n    #\n   \
  elsif ( $pg eq \"mustang\")\n      {\n	&flush_co\
mmand (\"rm ./bin/*\");\n	&flush_command (\"make $\
arguments all\");\n\n	if ( $OS=~/windows/){&flush_\
command(\"cp ./bin/* $BIN/mustang.exe\");}\n	else \
{&flush_command(\"cp ./bin/* $BIN/mustang\");}\n	\\
n	repo_store(\"$BIN/mustang\");\n      }\n\n	#\n	#\
 RNAplfold module\n	#\n    elsif ( $pg eq \"RNAplf\
old\")\n      {\n	&flush_command(\"./configure\");\
\n	&flush_command (\"make $arguments all\");\n	&ch\
eck_cp(\"./Progs/RNAplfold\", \"$BIN\");\n	&check_\
cp(\"./Progs/RNAalifold\", \"$BIN\");\n	&check_cp(\
\"./Progs/RNAfold\", \"$BIN\");\n	\n	repo_store(\"\
./Progs/RNAplfold\", \"./Progs/RNAalifold\", \"./P\
rogs/RNAfold\");\n      }\n      \n    #\n    # !!\
! RETREE module\n    #\n    elsif ( $pg eq \"retre\
e\")\n      {\n	chdir \"src\";\n	&flush_command (\\
"make $arguments all\");\n	&flush_command (\"make \
put\");\n	system \"cp ../exe/* $BIN\";\n	\n	repo_s\
tore(\"retree\", \"../exe\");\n      }\n	\n    chd\
ir $CDIR;\n    return &pg_is_installed ($pg, $BIN)\
;\n  }\n\nsub install_t_coffee\n  {\n    my ($pg)=\
(@_);\n    my ($report,$cflags, $arguments, $langu\
age, $compiler) ;\n    #1-Install T-Coffee\n    ch\
dir \"t_coffee_source\";\n    &flush_command (\"ma\
ke clean\");\n    print \"\\n------- Compiling T-C\
offee\\n\";\n    $language=$PG{$pg} {language2};\n\
    $arguments=$PG{$language}{arguments};\n\n    i\
f ( $CC ne \"\"){\n      print \"make -i $argument\
s t_coffee \\n\";\n      &flush_command (\"make -i\
 $arguments t_coffee\");\n    }\n    &check_cp ($p\
g, $BIN);\n    \n    chdir $CDIR;\n    return &pg_\
is_installed ($pg, $BIN);\n  }\nsub install_TMalig\
n\n  {\n    my ($pg)=(@_);\n    my $report;\n    c\
hdir \"t_coffee_source\";\n    print \"\\n------- \
Compiling TMalign\\n\";\n    `rm TMalign TMalign.e\
xe $SILENT`;\n    if ( $FC ne \"\"){&flush_command\
 (\"make -i $PG{Fortran}{arguments} TMalign\");}\n\
    &check_cp ($pg, $BIN);\n    repo_store($pg);\n\
\n    if ( !-e \"$BIN/$pg\" && pg_has_binary_distr\
ib ($pg))\n      {\n	print \"!!!!!!! Compilation o\
f $pg impossible. Will try to install from binary\\
\n\";\n	return &install_binary_package ($pg);\n   \
   }\n    chdir $CDIR;\n    return &pg_is_installe\
d ($pg, $BIN);\n  }\n\nsub pg_has_binary_distrib\n\
  {\n    my ($pg)=(@_);\n    if ($PG{$pg}{windows}\
){return 1;}\n    elsif ($PG{$pg}{osx}){return 1;}\
\n    elsif ($PG{$pg}{linux}){return 1;}\n    retu\
rn 0;\n  }\nsub install_binary_package\n  {\n    m\
y ($pg)=(@_);\n    my ($base,$report,$name, $downl\
oad, $arguments, $language, $dir);\n    my $isdir;\
\n    &input_os();\n    \n    #\n    # - paolodt -\
 Check if the module exists in the repository cach\
e \n    #\n	if( repo_load($pg) ) {\n	    $PG{$pg}{\
from_binary}=1;\n		return 1;\n	}\n    # - paolodt \
- end \n    \n    if (!&supported_os($OS)){return \
0;}\n    if ( $PG{$pg}{binary}){$name=$PG{$pg}{bin\
ary};}\n    else \n      {\n	$name=$pg;\n	if ( $OS\
 eq \"windows\"){$name.=\".exe\";}\n      }\n    \\
n    $download=\"$WEB_BASE/Packages/Binaries/$OS/$\
name\";\n    \n    $base=cwd();\n    chdir $TMP;\n\
    \n    if (!-e $name)\n      {\n	`rm x $SILENT`\
;\n	if ( url2file(\"$download\",\"x\")==$EXIT_SUCC\
ESS)\n	  {\n	    `mv x $name`;\n	  }\n      }\n   \
 \n    if (!-e $name)\n      {\n	print \"!!!!!!! $\
PG{$pg}{dname}: Download of $pg binary failed\\n\"\
;\n	print \"!!!!!!! $PG{$pg}{dname}: Check Address\
: $download\\n\";\n	return 0;\n      }\n    print \
\"\\n------- Installing $pg\\n\";\n    \n    if ($\
name =~/tar\\.gz/)\n      {\n	`gunzip  $name`;\n	`\
tar -xvf $pg.tar`;\n	chdir $pg;\n	if ( $pg eq \"ma\
fft\")\n	  {\n	    if ($ROOT_INSTALL)\n	      {\n	\
	&root_run (\"You Must be Roor to Install MAFFT\\n\
\", \"$CP mafft/bin/* /usr/local/mafft;mkdir /usr/\
local/mafft/; $CP mafft/lib/* /usr/local/bin/\");\\
n	      }\n	    else\n	      {\n		`$CP $TMP/$pg/bi\
n/* $BIN $SILENT`;\n		`$CP $TMP/$pg/lib/* $BIN $SI\
LENT`;\n	      }\n	  }\n	else\n	  {\n	    if (-e \\
"$TMP/$pg/data\"){`$CP $TMP/$pg/data/* $TCM $SILEN\
T`;}\n	    if (!($pg=~/\\*/)){`rm -rf $pg`;}\n	  }\
\n      }\n    else\n      {\n	&check_cp (\"$pg\",\
 \"$BIN\");\n	`chmod u+x $BIN/$pg`; \n	unlink ($pg\
);\n      }\n    chdir $base;\n    $PG{$pg}{from_b\
inary}=1;\n    return &pg_is_installed ($pg, $BIN)\
;\n  }\n\nsub add_dir \n  {\n    my $dir=@_[0];\n \
   \n    if (!-e $dir && !-d $dir)\n      {\n	my @\
l;\n	umask (0000);\n	@l=mkpath ($dir,{mode => 0777\
});\n	\n      }\n    else\n      {\n	return 0;\n  \
    }\n  }\nsub check_rm \n  {\n    my ($file)=(@_\
);\n    \n    if ( -e $file)\n      {\n	return unl\
ink($file);\n      }\n    return 0;\n  }\nsub chec\
k_cp\n  {\n    my ($from, $to)=(@_);\n    if ( !-e\
 $from && -e \"$from\\.exe\"){$from=\"$from\\.exe\\
";}\n    if ( !-e $from){return 0;}\n        \n   \
 `$CP $from $to`;\n    return 1;\n  }\n\nsub repo_\
store \n{\n   # check that all required data are a\
vailable\n   if( $REPO_ROOT eq \"\" ) { return; }\\
n\n\n    # extract the package name from the speci\
fied path\n    my $pg =`basename $_[0]`;\n    chom\
p($pg);\n	\n    my $VER = $PG{$pg}{version};\n    \
my $CACHE = \"$REPO_ROOT/$pg/$VER/$OSNAME-$OSARCH\\
"; \n    \n    print \"-------- Storing package: \\
\\"$pg\\\" to path: $CACHE\\n\";\n    \n    # clea\
n the cache path if exists and create it again\n  \
  `rm -rf $CACHE`;\n    `mkdir -p $CACHE`;\n    \n\
 	for my $path (@_) {\n\n	    # check if it is a s\
ingle file \n	 	if( -f $path ) {\n	    	`cp $path \
$CACHE`;\n		}\n		# .. or a directory, in this case\
 copy all the content \n		elsif( -d $path ) {\n			\
opendir(IMD, $path);\n			my @thefiles= readdir(IMD\
);\n			closedir(IMD);\n			\n			for my $_file (@the\
files) {\n				if( $_file ne \".\" && $_file ne \".\
.\") {\n	    			`cp $path/$_file $CACHE`;\n				}\n\
			}\n		} \n	}	   \n    \n	\n}   \n\nsub repo_load\
 \n{\n    my ($pg)=(@_);\n\n    # check that all r\
equired data are available\n    if( $REPO_ROOT eq \
\"\" ) { return 0; }\n\n    my $VER = $PG{$pg}{ver\
sion};\n    my $CACHE = \"$REPO_ROOT/$pg/$VER/$OSN\
AME-$OSARCH\"; \n    if( !-e \"$CACHE/$pg\" ) {\n \
  	 	print \"-------- Module \\\"$pg\\\" NOT found\
 on repository cache.\\n\";\n    	return 0;\n    }\
\n    \n    print \"-------- Module \\\"$pg\\\" fo\
und on repository cache. Using copy on path: $CACH\
E\\n\";\n    `cp $CACHE/* $BIN`;\n    return 1;\n}\
\n\nsub check_file_list_exists \n  {\n    my ($bas\
e, @flist)=(@_);\n    my $f;\n\n    foreach $f (@f\
list)\n      {\n	if ( !-e \"$base/$f\"){return 0;}\
\n      }\n    return 1;\n  }\nsub ls\n  {\n    my\
 $f=@_[0];\n    my @fl;\n    chomp(@fl=`ls -1 $f`)\
;\n    return @fl;\n  }\nsub flush_command\n  {\n \
   my $command=@_[0];\n    my $F=new FileHandle;\n\
    open ($F, \"$command|\");\n    while (<$F>){pr\
int \"    --- $_\";}\n    close ($F);\n  }    \n\n\
sub input_installation_directory\n  {\n    my $dir\
=@_[0];\n    my $new;\n    \n    print \"------- T\
he current installation directory is: [$dir]\\n\";\
\n    print \"??????? Return to keep the default o\
r new value:\";\n   \n    if ($NO_QUESTION==0)\n  \
    {\n	chomp ($new=<stdin>);\n	while ( $new ne \"\
\" && !input_yes (\"You have entered $new. Is this\
 correct? ([y]/n):\"))\n	  {\n	    print \"???????\
New installation directory:\";\n	    chomp ($new=<\
stdin>);\n	  }\n	$dir=($new eq \"\")?$dir:$new;\n	\
$dir=~s/\\/$//;\n      }\n    \n    if ( -d $dir){\
return $dir;}\n    elsif (&root_run (\"You must be\
 root to create $dir\",\"mkdir $dir\")==$EXIT_SUCC\
ESS){return $dir;}\n    else\n      {\n	print \"!!\
!!!!! $dir could not be created\\n\";\n	if ( $NO_Q\
UESTION)\n	  {\n	    return \"\";\n	  }\n	elsif ( \
&input_yes (\"??????? Do you want to provide a new\
 directory([y]/n)?:\"))\n	  {\n	    return input_i\
nstallation_directory ($dir);\n	  }\n	else\n	  {\n\
	    return \"\";\n	  }\n      }\n    \n  }\nsub i\
nput_yes\n  {\n    my $question =@_[0];\n    my $a\
nswer;\n\n    if ($NO_QUESTION==1){return 1;}\n   \
 \n    if ($question eq \"\"){$question=\"??????? \
Do you wish to proceed ([y]/n)?:\";}\n    print $q\
uestion;\n    chomp($answer=lc(<STDIN>));\n    if \
(($answer=~/^y/) || $answer eq \"\"){return 1;}\n \
   elsif ( ($answer=~/^n/)){return 0;}\n    else\n\
      {\n	return input_yes($question);\n      }\n \
 }\nsub root_run\n  {\n    my ($txt, $cmd)=(@_);\n\
    \n    if ( system ($cmd)==$EXIT_SUCCESS){retur\
n $EXIT_SUCCESS;}\n    else \n      {\n	print \"--\
----- $txt\\n\";\n	if ( $ROOT eq \"sudo\"){return \
system (\"sudo $cmd\");}\n	else {return system (\"\
su root -c \\\"$cmd\\\"\");}\n      }\n  }\nsub ge\
t_root\n  {\n    if (&pg_is_installed (\"sudo\")){\
return \"sudo\";}\n    else {return \"su\";}\n  }\\
n\nsub get_os\n  {\n    my $raw_os=`uname`;\n    m\
y $os;\n\n    $raw_os=lc ($raw_os);\n    \n    if \
($raw_os =~/cygwin/){$os=\"windows\";}\n    elsif \
($raw_os =~/linux/){$os=\"linux\";}\n    elsif ($r\
aw_os =~/osx/){$os=\"macosx\";}\n    elsif ($raw_o\
s =~/darwin/){$os=\"macosx\";}\n    else\n      {\\
n	$os=$raw_os;\n      }\n    return $os;\n  }\nsub\
 input_os\n  {\n    my $answer;\n    if ($OS) {ret\
urn $OS;}\n    \n    print \"??????? which os do y\
ou use: [w]indows, [l]inux, [m]acosx:?\";\n    $an\
swer=lc(<STDIN>);\n\n    if (($answer=~/^m/)){$OS=\
\"macosx\";}\n    elsif ( ($answer=~/^w/)){$OS=\"w\
indows\";}\n    elsif ( ($answer=~/^linux/)){$OS=\\
"linux\";}\n    \n    else\n      {\n	return &inpu\
t_os();\n      }\n    return $OS;\n  }\n\nsub supp\
orted_os\n  {\n    my ($os)=(@_[0]);\n    return $\
SUPPORTED_OS{$os};\n  }\n    \n    \n\n\nsub updat\
e_tclinkdb \n  {\n    my $file =@_[0];\n    my $na\
me;\n    my $F=new FileHandle;\n    my ($download,\
 $address, $name, $l, $db);\n    \n    if ( $file \
eq \"update\"){$file=$TCLINKDB_ADDRESS;}\n    \n  \
  if ( $file =~/http:\\/\\// || $file =~/ftp:\\/\\\
//)\n      {\n	($address, $name)=($download=~/(.*)\
\\/([^\\/]+)$/);\n	`rm x $SILENT`;\n	if (&url2file\
 ($file,\"x\")==$EXIT_SUCCESS)\n	  {\n	    print \\
"------- Susscessful upload of $name\";\n	    `mv \
x $name`;\n	    $file=$name;\n	  }\n      }\n    o\
pen ($F, \"$file\");\n    while (<$F>)\n      {\n	\
my $l=$_;\n	if (($l =~/^\\/\\//) || ($db=~/^#/)){;\
}\n	elsif ( !($l =~/\\w/)){;}\n	else\n	  {\n	    m\
y @v=split (/\\s+/, $l);\n	    if ( $l=~/^MODE/)\n\
	      {\n		$MODE{$v[1]}{$v[2]}=$v[3];\n	      }\n\
	    elsif ($l=~/^PG/)\n	      {\n		$PG{$v[1]}{$v[\
2]}=$v[3];\n	      }\n	  }\n      }\n    close ($F\
);\n    &post_process_PG();\n    return;\n  }\n\n\\
n\nsub initialize_PG\n  {\n\n$PG{\"t_coffee\"}{\"4\
_TCOFFEE\"}=\"TCOFFEE\";\n$PG{\"t_coffee\"}{\"type\
\"}=\"sequence_multiple_aligner\";\n$PG{\"t_coffee\
\"}{\"ADDRESS\"}=\"http://www.tcoffee.org\";\n$PG{\
\"t_coffee\"}{\"language\"}=\"C++\";\n$PG{\"t_coff\
ee\"}{\"language2\"}=\"CXX\";\n$PG{\"t_coffee\"}{\\
"source\"}=\"http://www.tcoffee.org/Packages/T-COF\
FEE_distribution.tar.gz\";\n$PG{\"t_coffee\"}{\"up\
date_action\"}=\"always\";\n$PG{\"t_coffee\"}{\"mo\
de\"}=\"tcoffee,mcoffee,rcoffee,expresso,3dcoffee\\
";\n$PG{\"clustalo\"}{\"4_TCOFFEE\"}=\"CLUSTALO\";\
\n$PG{\"clustalo\"}{\"type\"}=\"sequence_multiple_\
aligner\";\n$PG{\"clustalo\"}{\"ADDRESS\"}=\"http:\
//www.clustal.org/omega/\";\n$PG{\"clustalo\"}{\"l\
anguage\"}=\"C++\";\n$PG{\"clustalo\"}{\"language2\
\"}=\"C++\";\n$PG{\"clustalo\"}{\"source\"}=\"http\
://www.clustal.org/omega/clustal-omega-1.1.0.tar.g\
z\";\n$PG{\"clustalo\"}{\"mode\"}=\"mcoffee\";\n$P\
G{\"clustalo\"}{\"version\"}=\"1.1.0\";\n$PG{\"str\
ike\"}{\"4_TCOFFEE\"}=\"STRIKE\";\n$PG{\"strike\"}\
{\"type\"}=\"sequence_alignment_scoring\";\n$PG{\"\
strike\"}{\"ADDRESS\"}=\"http://www.tcoffee.org/Pr\
ojects/strike/index.html\";\n$PG{\"strike\"}{\"lan\
guage\"}=\"C++\";\n$PG{\"strike\"}{\"language2\"}=\
\"CXX\";\n$PG{\"strike\"}{\"source\"}=\"http://www\
.tcoffee.org/Projects/strike/strike_v1.2.tar.bz2\"\
;\n$PG{\"strike\"}{\"mode\"}=\"tcoffee,expresso\";\
\n$PG{\"strike\"}{\"version\"}=\"1.2\";\n$PG{\"clu\
stalw2\"}{\"4_TCOFFEE\"}=\"CLUSTALW2\";\n$PG{\"clu\
stalw2\"}{\"type\"}=\"sequence_multiple_aligner\";\
\n$PG{\"clustalw2\"}{\"ADDRESS\"}=\"http://www.clu\
stal.org\";\n$PG{\"clustalw2\"}{\"language\"}=\"C+\
+\";\n$PG{\"clustalw2\"}{\"language2\"}=\"CXX\";\n\
$PG{\"clustalw2\"}{\"source\"}=\"http://www.clusta\
l.org/download/2.0.10/clustalw-2.0.10-src.tar.gz\"\
;\n$PG{\"clustalw2\"}{\"mode\"}=\"mcoffee,rcoffee\\
";\n$PG{\"clustalw2\"}{\"version\"}=\"2.0.10\";\n$\
PG{\"clustalw\"}{\"4_TCOFFEE\"}=\"CLUSTALW\";\n$PG\
{\"clustalw\"}{\"type\"}=\"sequence_multiple_align\
er\";\n$PG{\"clustalw\"}{\"ADDRESS\"}=\"http://www\
.clustal.org\";\n$PG{\"clustalw\"}{\"language\"}=\\
"C\";\n$PG{\"clustalw\"}{\"language2\"}=\"C\";\n$P\
G{\"clustalw\"}{\"source\"}=\"http://www.clustal.o\
rg/download/1.X/ftp-igbmc.u-strasbg.fr/pub/Clustal\
W/clustalw1.82.UNIX.tar.gz\";\n$PG{\"clustalw\"}{\\
"mode\"}=\"mcoffee,rcoffee\";\n$PG{\"clustalw\"}{\\
"version\"}=\"1.82\";\n$PG{\"dialign-t\"}{\"4_TCOF\
FEE\"}=\"DIALIGNT\";\n$PG{\"dialign-t\"}{\"type\"}\
=\"sequence_multiple_aligner\";\n$PG{\"dialign-t\"\
}{\"ADDRESS\"}=\"http://dialign-tx.gobics.de/\";\n\
$PG{\"dialign-t\"}{\"DIR\"}=\"/usr/share/dialign-t\
x/\";\n$PG{\"dialign-t\"}{\"language\"}=\"C\";\n$P\
G{\"dialign-t\"}{\"language2\"}=\"C\";\n$PG{\"dial\
ign-t\"}{\"source\"}=\"http://dialign-tx.gobics.de\
/DIALIGN-TX_1.0.2.tar.gz\";\n$PG{\"dialign-t\"}{\"\
mode\"}=\"mcoffee\";\n$PG{\"dialign-t\"}{\"binary\\
"}=\"dialign-t\";\n$PG{\"dialign-t\"}{\"version\"}\
=\"1.0.2\";\n$PG{\"dialign-tx\"}{\"4_TCOFFEE\"}=\"\
DIALIGNTX\";\n$PG{\"dialign-tx\"}{\"type\"}=\"sequ\
ence_multiple_aligner\";\n$PG{\"dialign-tx\"}{\"AD\
DRESS\"}=\"http://dialign-tx.gobics.de/\";\n$PG{\"\
dialign-tx\"}{\"DIR\"}=\"/usr/share/dialign-tx/\";\
\n$PG{\"dialign-tx\"}{\"language\"}=\"C\";\n$PG{\"\
dialign-tx\"}{\"language2\"}=\"C\";\n$PG{\"dialign\
-tx\"}{\"source\"}=\"http://dialign-tx.gobics.de/D\
IALIGN-TX_1.0.2.tar.gz\";\n$PG{\"dialign-tx\"}{\"m\
ode\"}=\"mcoffee\";\n$PG{\"dialign-tx\"}{\"binary\\
"}=\"dialign-tx\";\n$PG{\"dialign-tx\"}{\"version\\
"}=\"1.0.2\";\n$PG{\"poa\"}{\"4_TCOFFEE\"}=\"POA\"\
;\n$PG{\"poa\"}{\"type\"}=\"sequence_multiple_alig\
ner\";\n$PG{\"poa\"}{\"ADDRESS\"}=\"http://www.bio\
informatics.ucla.edu/poa/\";\n$PG{\"poa\"}{\"langu\
age\"}=\"C\";\n$PG{\"poa\"}{\"language2\"}=\"C\";\\
n$PG{\"poa\"}{\"source\"}=\"http://downloads.sourc\
eforge.net/poamsa/poaV2.tar.gz\";\n$PG{\"poa\"}{\"\
DIR\"}=\"/usr/share/\";\n$PG{\"poa\"}{\"FILE1\"}=\\
"blosum80.mat\";\n$PG{\"poa\"}{\"mode\"}=\"mcoffee\
\";\n$PG{\"poa\"}{\"binary\"}=\"poa\";\n$PG{\"poa\\
"}{\"version\"}=\"2.0\";\n$PG{\"probcons\"}{\"4_TC\
OFFEE\"}=\"PROBCONS\";\n$PG{\"probcons\"}{\"type\"\
}=\"sequence_multiple_aligner\";\n$PG{\"probcons\"\
}{\"ADDRESS\"}=\"http://probcons.stanford.edu/\";\\
n$PG{\"probcons\"}{\"language2\"}=\"CXX\";\n$PG{\"\
probcons\"}{\"language\"}=\"C++\";\n$PG{\"probcons\
\"}{\"source\"}=\"http://probcons.stanford.edu/pro\
bcons_v1_12.tar.gz\";\n$PG{\"probcons\"}{\"mode\"}\
=\"mcoffee\";\n$PG{\"probcons\"}{\"binary\"}=\"pro\
bcons\";\n$PG{\"probcons\"}{\"version\"}=\"1.12\";\
\n$PG{\"mafft\"}{\"4_TCOFFEE\"}=\"MAFFT\";\n$PG{\"\
mafft\"}{\"type\"}=\"sequence_multiple_aligner\";\\
n$PG{\"mafft\"}{\"ADDRESS\"}=\"http://align.bmr.ky\
ushu-u.ac.jp/mafft/online/server/\";\n$PG{\"mafft\\
"}{\"language\"}=\"C\";\n$PG{\"mafft\"}{\"language\
\"}=\"C\";\n$PG{\"mafft\"}{\"source\"}=\"http://al\
ign.bmr.kyushu-u.ac.jp/mafft/software/mafft-6.603-\
with-extensions-src.tgz\";\n$PG{\"mafft\"}{\"windo\
ws\"}=\"http://align.bmr.kyushu-u.ac.jp/mafft/soft\
ware/mafft-6.603-mingw.tar\";\n$PG{\"mafft\"}{\"mo\
de\"}=\"mcoffee,rcoffee\";\n$PG{\"mafft\"}{\"binar\
y\"}=\"mafft.tar.gz\";\n$PG{\"mafft\"}{\"version\"\
}=\"6.603\";\n$PG{\"muscle\"}{\"4_TCOFFEE\"}=\"MUS\
CLE\";\n$PG{\"muscle\"}{\"type\"}=\"sequence_multi\
ple_aligner\";\n$PG{\"muscle\"}{\"ADDRESS\"}=\"htt\
p://www.drive5.com/muscle/\";\n$PG{\"muscle\"}{\"l\
anguage\"}=\"C++\";\n$PG{\"muscle\"}{\"language2\"\
}=\"GPP\";\n$PG{\"muscle\"}{\"source\"}=\"http://w\
ww.drive5.com/muscle/downloads3.7/muscle3.7_src.ta\
r.gz\";\n$PG{\"muscle\"}{\"windows\"}=\"http://www\
.drive5.com/muscle/downloads3.7/muscle3.7_win32.zi\
p\";\n$PG{\"muscle\"}{\"linux\"}=\"http://www.driv\
e5.com/muscle/downloads3.7/muscle3.7_linux_ia32.ta\
r.gz\";\n$PG{\"muscle\"}{\"mode\"}=\"mcoffee,rcoff\
ee\";\n$PG{\"muscle\"}{\"version\"}=\"3.7\";\n$PG{\
\"mus4\"}{\"4_TCOFFEE\"}=\"MUS4\";\n$PG{\"mus4\"}{\
\"type\"}=\"sequence_multiple_aligner\";\n$PG{\"mu\
s4\"}{\"ADDRESS\"}=\"http://www.drive5.com/muscle/\
\";\n$PG{\"mus4\"}{\"language\"}=\"C++\";\n$PG{\"m\
us4\"}{\"language2\"}=\"GPP\";\n$PG{\"mus4\"}{\"so\
urce\"}=\"http://www.drive5.com/muscle/muscle4.0_s\
rc.tar.gz\";\n$PG{\"mus4\"}{\"mode\"}=\"mcoffee,rc\
offee\";\n$PG{\"mus4\"}{\"version\"}=\"4.0\";\n$PG\
{\"pcma\"}{\"4_TCOFFEE\"}=\"PCMA\";\n$PG{\"pcma\"}\
{\"type\"}=\"sequence_multiple_aligner\";\n$PG{\"p\
cma\"}{\"ADDRESS\"}=\"ftp://iole.swmed.edu/pub/PCM\
A/\";\n$PG{\"pcma\"}{\"language\"}=\"C\";\n$PG{\"p\
cma\"}{\"language2\"}=\"C\";\n$PG{\"pcma\"}{\"sour\
ce\"}=\"ftp://iole.swmed.edu/pub/PCMA/pcma.tar.gz\\
";\n$PG{\"pcma\"}{\"mode\"}=\"mcoffee\";\n$PG{\"pc\
ma\"}{\"version\"}=\"1.0\";\n$PG{\"kalign\"}{\"4_T\
COFFEE\"}=\"KALIGN\";\n$PG{\"kalign\"}{\"type\"}=\\
"sequence_multiple_aligner\";\n$PG{\"kalign\"}{\"A\
DDRESS\"}=\"http://msa.cgb.ki.se\";\n$PG{\"kalign\\
"}{\"language\"}=\"C\";\n$PG{\"kalign\"}{\"languag\
e2\"}=\"C\";\n$PG{\"kalign\"}{\"source\"}=\"http:/\
/msa.cgb.ki.se/downloads/kalign/current.tar.gz\";\\
n$PG{\"kalign\"}{\"mode\"}=\"mcoffee\";\n$PG{\"kal\
ign\"}{\"version\"}=\"1.0\";\n$PG{\"amap\"}{\"4_TC\
OFFEE\"}=\"AMAP\";\n$PG{\"amap\"}{\"type\"}=\"sequ\
ence_multiple_aligner\";\n$PG{\"amap\"}{\"ADDRESS\\
"}=\"http://bio.math.berkeley.edu/amap/\";\n$PG{\"\
amap\"}{\"language\"}=\"C++\";\n$PG{\"amap\"}{\"la\
nguage2\"}=\"CXX\";\n$PG{\"amap\"}{\"source\"}=\"h\
ttp://amap-align.googlecode.com/files/amap.2.0.tar\
.gz\";\n$PG{\"amap\"}{\"mode\"}=\"mcoffee\";\n$PG{\
\"amap\"}{\"version\"}=\"2.0\";\n$PG{\"proda\"}{\"\
4_TCOFFEE\"}=\"PRODA\";\n$PG{\"proda\"}{\"type\"}=\
\"sequence_multiple_aligner\";\n$PG{\"proda\"}{\"A\
DDRESS\"}=\"http://proda.stanford.edu\";\n$PG{\"pr\
oda\"}{\"language\"}=\"C++\";\n$PG{\"proda\"}{\"la\
nguage2\"}=\"CXX\";\n$PG{\"proda\"}{\"source\"}=\"\
http://proda.stanford.edu/proda_1_0.tar.gz\";\n$PG\
{\"proda\"}{\"mode\"}=\"mcoffee\";\n$PG{\"proda\"}\
{\"version\"}=\"1.0\";\n$PG{\"fsa\"}{\"4_TCOFFEE\"\
}=\"FSA\";\n$PG{\"fsa\"}{\"type\"}=\"sequence_mult\
iple_aligner\";\n$PG{\"fsa\"}{\"ADDRESS\"}=\"http:\
//fsa.sourceforge.net/\";\n$PG{\"fsa\"}{\"language\
\"}=\"C++\";\n$PG{\"fsa\"}{\"language2\"}=\"CXX\";\
\n$PG{\"fsa\"}{\"source\"}=\"http://sourceforge.ne\
t/projects/fsa/files/fsa-1.15.3.tar.gz/download/\"\
;\n$PG{\"fsa\"}{\"mode\"}=\"mcoffee\";\n$PG{\"fsa\\
"}{\"version\"}=\"1.15.3\";\n$PG{\"prank\"}{\"4_TC\
OFFEE\"}=\"PRANK\";\n$PG{\"prank\"}{\"type\"}=\"se\
quence_multiple_aligner\";\n$PG{\"prank\"}{\"ADDRE\
SS\"}=\"http://www.ebi.ac.uk/goldman-srv/prank/\";\
\n$PG{\"prank\"}{\"language\"}=\"C++\";\n$PG{\"pra\
nk\"}{\"language2\"}=\"CXX\";\n$PG{\"prank\"}{\"so\
urce\"}=\"http://www.ebi.ac.uk/goldman-srv/prank/s\
rc/prank/prank.src.100802.tgz\";\n$PG{\"prank\"}{\\
"mode\"}=\"mcoffee\";\n$PG{\"prank\"}{\"version\"}\
=\"100303\";\n$PG{\"sap\"}{\"4_TCOFFEE\"}=\"SAP\";\
\n$PG{\"sap\"}{\"type\"}=\"structure_pairwise_alig\
ner\";\n$PG{\"sap\"}{\"ADDRESS\"}=\"http://mathbio\
.nimr.mrc.ac.uk/wiki/Software\";\n$PG{\"sap\"}{\"l\
anguage\"}=\"C\";\n$PG{\"sap\"}{\"language2\"}=\"C\
\";\n$PG{\"sap\"}{\"source\"}=\"http://mathbio.nim\
r.mrc.ac.uk/download/SAP/sap-1.1.3.tar.gz\";\n$PG{\
\"sap\"}{\"mode\"}=\"expresso,3dcoffee\";\n$PG{\"s\
ap\"}{\"version\"}=\"1.1.3\";\n$PG{\"TMalign\"}{\"\
4_TCOFFEE\"}=\"TMALIGN\";\n$PG{\"TMalign\"}{\"type\
\"}=\"structure_pairwise_aligner\";\n$PG{\"TMalign\
\"}{\"ADDRESS\"}=\"http://zhanglab.ccmb.med.umich.\
edu/TM-align/TMalign.f\";\n$PG{\"TMalign\"}{\"lang\
uage\"}=\"Fortran\";\n$PG{\"TMalign\"}{\"language2\
\"}=\"Fortran\";\n$PG{\"TMalign\"}{\"source\"}=\"h\
ttp://zhanglab.ccmb.med.umich.edu/TM-align/TMalign\
.f\";\n$PG{\"TMalign\"}{\"linux\"}=\"http://zhangl\
ab.ccmb.med.umich.edu/TM-align/TMalign_32.gz\";\n$\
PG{\"TMalign\"}{\"mode\"}=\"expresso,3dcoffee\";\n\
$PG{\"TMalign\"}{\"version\"}=\"2011.01.30\";\n$PG\
{\"mustang\"}{\"4_TCOFFEE\"}=\"MUSTANG\";\n$PG{\"m\
ustang\"}{\"type\"}=\"structure_pairwise_aligner\"\
;\n$PG{\"mustang\"}{\"ADDRESS\"}=\"http://www.cs.m\
u.oz.au/~arun/mustang\";\n$PG{\"mustang\"}{\"langu\
age\"}=\"C++\";\n$PG{\"mustang\"}{\"language2\"}=\\
"CXX\";\n$PG{\"mustang\"}{\"source\"}=\"http://ww2\
.cs.mu.oz.au/~arun/mustang/mustang_v3.2.1.tgz\";\n\
$PG{\"mustang\"}{\"mode\"}=\"expresso,3dcoffee\";\\
n$PG{\"mustang\"}{\"version\"}=\"3.2.1\";\n$PG{\"l\
sqman\"}{\"4_TCOFFEE\"}=\"LSQMAN\";\n$PG{\"lsqman\\
"}{\"type\"}=\"structure_pairwise_aligner\";\n$PG{\
\"lsqman\"}{\"ADDRESS\"}=\"empty\";\n$PG{\"lsqman\\
"}{\"language\"}=\"empty\";\n$PG{\"lsqman\"}{\"lan\
guage2\"}=\"empty\";\n$PG{\"lsqman\"}{\"source\"}=\
\"empty\";\n$PG{\"lsqman\"}{\"update_action\"}=\"n\
ever\";\n$PG{\"lsqman\"}{\"mode\"}=\"expresso,3dco\
ffee\";\n$PG{\"align_pdb\"}{\"4_TCOFFEE\"}=\"ALIGN\
_PDB\";\n$PG{\"align_pdb\"}{\"type\"}=\"structure_\
pairwise_aligner\";\n$PG{\"align_pdb\"}{\"ADDRESS\\
"}=\"empty\";\n$PG{\"align_pdb\"}{\"language\"}=\"\
empty\";\n$PG{\"align_pdb\"}{\"language2\"}=\"empt\
y\";\n$PG{\"align_pdb\"}{\"source\"}=\"empty\";\n$\
PG{\"align_pdb\"}{\"update_action\"}=\"never\";\n$\
PG{\"align_pdb\"}{\"mode\"}=\"expresso,3dcoffee\";\
\n$PG{\"fugueali\"}{\"4_TCOFFEE\"}=\"FUGUE\";\n$PG\
{\"fugueali\"}{\"type\"}=\"structure_pairwise_alig\
ner\";\n$PG{\"fugueali\"}{\"ADDRESS\"}=\"http://ww\
w-cryst.bioc.cam.ac.uk/fugue/download.html\";\n$PG\
{\"fugueali\"}{\"language\"}=\"empty\";\n$PG{\"fug\
ueali\"}{\"language2\"}=\"empty\";\n$PG{\"fugueali\
\"}{\"source\"}=\"empty\";\n$PG{\"fugueali\"}{\"up\
date_action\"}=\"never\";\n$PG{\"fugueali\"}{\"mod\
e\"}=\"expresso,3dcoffee\";\n$PG{\"dalilite.pl\"}{\
\"4_TCOFFEE\"}=\"DALILITEc\";\n$PG{\"dalilite.pl\"\
}{\"type\"}=\"structure_pairwise_aligner\";\n$PG{\\
"dalilite.pl\"}{\"ADDRESS\"}=\"built_in\";\n$PG{\"\
dalilite.pl\"}{\"ADDRESS2\"}=\"http://www.ebi.ac.u\
k/Tools/webservices/services/dalilite\";\n$PG{\"da\
lilite.pl\"}{\"language\"}=\"Perl\";\n$PG{\"dalili\
te.pl\"}{\"language2\"}=\"Perl\";\n$PG{\"dalilite.\
pl\"}{\"source\"}=\"empty\";\n$PG{\"dalilite.pl\"}\
{\"update_action\"}=\"never\";\n$PG{\"dalilite.pl\\
"}{\"mode\"}=\"expresso,3dcoffee\";\n$PG{\"probcon\
sRNA\"}{\"4_TCOFFEE\"}=\"PROBCONSRNA\";\n$PG{\"pro\
bconsRNA\"}{\"type\"}=\"RNA_multiple_aligner\";\n$\
PG{\"probconsRNA\"}{\"ADDRESS\"}=\"http://probcons\
.stanford.edu/\";\n$PG{\"probconsRNA\"}{\"language\
\"}=\"C++\";\n$PG{\"probconsRNA\"}{\"language2\"}=\
\"CXX\";\n$PG{\"probconsRNA\"}{\"source\"}=\"http:\
//probcons.stanford.edu/probconsRNA.tar.gz\";\n$PG\
{\"probconsRNA\"}{\"mode\"}=\"mcoffee,rcoffee\";\n\
$PG{\"probconsRNA\"}{\"version\"}=\"1.0\";\n$PG{\"\
sfold\"}{\"4_TCOFFEE\"}=\"CONSAN\";\n$PG{\"sfold\"\
}{\"type\"}=\"RNA_pairwise_aligner\";\n$PG{\"sfold\
\"}{\"ADDRESS\"}=\"http://selab.janelia.org/softwa\
re/consan/\";\n$PG{\"sfold\"}{\"language\"}=\"empt\
y\";\n$PG{\"sfold\"}{\"language2\"}=\"empty\";\n$P\
G{\"sfold\"}{\"source\"}=\"empty\";\n$PG{\"sfold\"\
}{\"update_action\"}=\"never\";\n$PG{\"sfold\"}{\"\
mode\"}=\"rcoffee\";\n$PG{\"RNAplfold\"}{\"4_TCOFF\
EE\"}=\"RNAPLFOLD\";\n$PG{\"RNAplfold\"}{\"type\"}\
=\"RNA_secondarystructure_predictor\";\n$PG{\"RNAp\
lfold\"}{\"ADDRESS\"}=\"http://www.tbi.univie.ac.a\
t/~ivo/RNA/\";\n$PG{\"RNAplfold\"}{\"language\"}=\\
"C\";\n$PG{\"RNAplfold\"}{\"language2\"}=\"C\";\n$\
PG{\"RNAplfold\"}{\"source\"}=\"http://www.tbi.uni\
vie.ac.at/~ivo/RNA/ViennaRNA-1.7.2.tar.gz\";\n$PG{\
\"RNAplfold\"}{\"mode\"}=\"rcoffee,\";\n$PG{\"RNAp\
lfold\"}{\"version\"}=\"1.7.2\";\n$PG{\"retree\"}{\
\"4_TCOFFEE\"}=\"PHYLIP\";\n$PG{\"retree\"}{\"type\
\"}=\"RNA_secondarystructure_predictor\";\n$PG{\"r\
etree\"}{\"ADDRESS\"}=\"http://evolution.gs.washin\
gton.edu/phylip/\";\n$PG{\"retree\"}{\"language\"}\
=\"C\";\n$PG{\"retree\"}{\"language2\"}=\"C\";\n$P\
G{\"retree\"}{\"source\"}=\"http://evolution.gs.wa\
shington.edu/phylip/download/phylip-3.69.tar.gz\";\
\n$PG{\"retree\"}{\"mode\"}=\"trmsd,\";\n$PG{\"ret\
ree\"}{\"version\"}=\"3.69\";\n$PG{\"hmmtop\"}{\"4\
_TCOFFEE\"}=\"HMMTOP\";\n$PG{\"hmmtop\"}{\"type\"}\
=\"protein_secondarystructure_predictor\";\n$PG{\"\
hmmtop\"}{\"ADDRESS\"}=\"www.enzim.hu/hmmtop/\";\n\
$PG{\"hmmtop\"}{\"language\"}=\"C\";\n$PG{\"hmmtop\
\"}{\"language2\"}=\"C\";\n$PG{\"hmmtop\"}{\"sourc\
e\"}=\"empty\";\n$PG{\"hmmtop\"}{\"binary\"}=\"hmm\
top\";\n$PG{\"hmmtop\"}{\"update_action\"}=\"never\
\";\n$PG{\"hmmtop\"}{\"mode\"}=\"tcoffee\";\n$PG{\\
"hmmtop\"}{\"version\"}=\"2.1\";\n$PG{\"gorIV\"}{\\
"4_TCOFFEE\"}=\"GOR4\";\n$PG{\"gorIV\"}{\"type\"}=\
\"protein_secondarystructure_predictor\";\n$PG{\"g\
orIV\"}{\"ADDRESS\"}=\"http://mig.jouy.inra.fr/log\
iciels/gorIV/\";\n$PG{\"gorIV\"}{\"language\"}=\"C\
\";\n$PG{\"gorIV\"}{\"language2\"}=\"C\";\n$PG{\"g\
orIV\"}{\"source\"}=\"http://mig.jouy.inra.fr/logi\
ciels/gorIV/GOR_IV.tar.gz\";\n$PG{\"gorIV\"}{\"upd\
ate_action\"}=\"never\";\n$PG{\"gorIV\"}{\"mode\"}\
=\"tcoffee\";\n$PG{\"wublast.pl\"}{\"4_TCOFFEE\"}=\
\"EBIWUBLASTc\";\n$PG{\"wublast.pl\"}{\"type\"}=\"\
protein_homology_predictor\";\n$PG{\"wublast.pl\"}\
{\"ADDRESS\"}=\"built_in\";\n$PG{\"wublast.pl\"}{\\
"ADDRESS2\"}=\"http://www.ebi.ac.uk/Tools/webservi\
ces/services/wublast\";\n$PG{\"wublast.pl\"}{\"lan\
guage\"}=\"Perl\";\n$PG{\"wublast.pl\"}{\"language\
2\"}=\"Perl\";\n$PG{\"wublast.pl\"}{\"source\"}=\"\
empty\";\n$PG{\"wublast.pl\"}{\"update_action\"}=\\
"never\";\n$PG{\"wublast.pl\"}{\"mode\"}=\"psicoff\
ee,expresso,accurate\";\n$PG{\"blastpgp.pl\"}{\"4_\
TCOFFEE\"}=\"EBIBLASTPGPc\";\n$PG{\"blastpgp.pl\"}\
{\"type\"}=\"protein_homology_predictor\";\n$PG{\"\
blastpgp.pl\"}{\"ADDRESS\"}=\"built_in\";\n$PG{\"b\
lastpgp.pl\"}{\"ADDRESS2\"}=\"http://www.ebi.ac.uk\
/Tools/webservices/services/blastpgp\";\n$PG{\"bla\
stpgp.pl\"}{\"language\"}=\"Perl\";\n$PG{\"blastpg\
p.pl\"}{\"language2\"}=\"Perl\";\n$PG{\"blastpgp.p\
l\"}{\"source\"}=\"empty\";\n$PG{\"blastpgp.pl\"}{\
\"update_action\"}=\"never\";\n$PG{\"blastpgp.pl\"\
}{\"mode\"}=\"psicoffee,expresso,accurate\";\n$PG{\
\"blastall\"}{\"4_TCOFFEE\"}=\"blastall\";\n$PG{\"\
blastall\"}{\"type\"}=\"protein_homology_predictor\
\";\n$PG{\"blastall\"}{\"ADDRESS\"}=\"ftp://ftp.nc\
bi.nih.gov/blast/executables/LATEST\";\n$PG{\"blas\
tall\"}{\"language\"}=\"C\";\n$PG{\"blastall\"}{\"\
language2\"}=\"C\";\n$PG{\"blastall\"}{\"source\"}\
=\"empty\";\n$PG{\"blastall\"}{\"update_action\"}=\
\"never\";\n$PG{\"blastall\"}{\"mode\"}=\"psicoffe\
e,expresso,3dcoffee\";\n$PG{\"legacy_blast.pl\"}{\\
"4_TCOFFEE\"}=\"NCBIBLAST\";\n$PG{\"legacy_blast.p\
l\"}{\"type\"}=\"protein_homology_predictor\";\n$P\
G{\"legacy_blast.pl\"}{\"ADDRESS\"}=\"ftp://ftp.nc\
bi.nih.gov/blast/executables/LATEST\";\n$PG{\"lega\
cy_blast.pl\"}{\"language\"}=\"C\";\n$PG{\"legacy_\
blast.pl\"}{\"language2\"}=\"C\";\n$PG{\"legacy_bl\
ast.pl\"}{\"source\"}=\"empty\";\n$PG{\"legacy_bla\
st.pl\"}{\"update_action\"}=\"never\";\n$PG{\"lega\
cy_blast.pl\"}{\"mode\"}=\"psicoffee,expresso,3dco\
ffee\";\n$PG{\"SOAP::Lite\"}{\"4_TCOFFEE\"}=\"SOAP\
LITE\";\n$PG{\"SOAP::Lite\"}{\"type\"}=\"library\"\
;\n$PG{\"SOAP::Lite\"}{\"ADDRESS\"}=\"http://cpans\
earch.perl.org/src/MKUTTER/SOAP-Lite-0.710.08/Make\
file.PL\";\n$PG{\"SOAP::Lite\"}{\"language\"}=\"Pe\
rl\";\n$PG{\"SOAP::Lite\"}{\"language2\"}=\"Perl\"\
;\n$PG{\"SOAP::Lite\"}{\"source\"}=\"empty\";\n$PG\
{\"blastpgp\"}{\"update_action\"}=\"never\";\n$PG{\
\"SOAP::Lite\"}{\"mode\"}=\"none\";\n$PG{\"XML::Si\
mple\"}{\"4_TCOFFEE\"}=\"XMLSIMPLE\";\n$PG{\"XML::\
Simple\"}{\"type\"}=\"library\";\n$PG{\"XML::Simpl\
e\"}{\"ADDRESS\"}=\"http://search.cpan.org/~grantm\
/XML-Simple-2.18/lib/XML/Simple.pm\";\n$PG{\"XML::\
Simple\"}{\"language\"}=\"Perl\";\n$PG{\"XML::Simp\
le\"}{\"language2\"}=\"Perl\";\n$PG{\"XML::Simple\\
"}{\"source\"}=\"empty\";\n$PG{\"XML::Simple\"}{\"\
mode\"}=\"psicoffee,expresso,accurate\";\n$MODE{\"\
tcoffee\"}{\"name\"}=\"tcoffee\";\n$MODE{\"rcoffee\
\"}{\"name\"}=\"rcoffee\";\n$MODE{\"3dcoffee\"}{\"\
name\"}=\"3dcoffee\";\n$MODE{\"mcoffee\"}{\"name\"\
}=\"mcoffee\";\n$MODE{\"expresso\"}{\"name\"}=\"ex\
presso\";\n$MODE{\"trmsd\"}{\"name\"}=\"trmsd\";\n\
$MODE{\"accurate\"}{\"name\"}=\"accurate\";\n$MODE\
{\"seq_reformat\"}{\"name\"}=\"seq_reformat\";\n\n\
\n$PG{C}{compiler}=\"gcc\";\n$PG{C}{compiler_flag}\
=\"CC\";\n$PG{C}{options}=\"\";\n$PG{C}{options_fl\
ag}=\"CFLAGS\";\n$PG{C}{type}=\"compiler\";\n\n$PG\
{\"CXX\"}{compiler}=\"g++\";\n$PG{\"CXX\"}{compile\
r_flag}=\"CXX\";\n$PG{\"CXX\"}{options}=\"\";\n$PG\
{\"CXX\"}{options_flag}=\"CXXFLAGS\";\n$PG{CXX}{ty\
pe}=\"compiler\";\n\n$PG{\"CPP\"}{compiler}=\"g++\\
";\n$PG{\"CPP\"}{compiler_flag}=\"CPP\";\n$PG{\"CP\
P\"}{options}=\"\";\n$PG{\"CPP\"}{options_flag}=\"\
CPPFLAGS\";\n$PG{CPP}{type}=\"compiler\";\n\n$PG{\\
"GPP\"}{compiler}=\"g++\";\n$PG{\"GPP\"}{compiler_\
flag}=\"GPP\";\n$PG{\"GPP\"}{options}=\"\";\n$PG{\\
"GPP\"}{options_flag}=\"CFLAGS\";\n$PG{GPP}{type}=\
\"compiler\";\n\n$PG{Fortran}{compiler}=\"g77\";\n\
$PG{Fortran}{compiler_flag}=\"FCC\";\n$PG{Fortran}\
{type}=\"compiler\";\n\n$PG{Perl}{compiler}=\"CPAN\
\";\n$PG{Perl}{type}=\"compiler\";\n\n$SUPPORTED_O\
S{macox}=\"Macintosh\";\n$SUPPORTED_OS{linux}=\"Li\
nux\";\n$SUPPORTED_OS{windows}=\"Cygwin\";\n\n\n\n\
$MODE{t_coffee}{description}=\" for regular multip\
le sequence alignments\";\n$MODE{rcoffee} {descrip\
tion}=\" for RNA multiple sequence alignments\";\n\
\n$MODE{psicoffee} {description}=\" for Homology E\
xtended multiple sequence alignments\";\n$MODE{exp\
resso}{description}=\" for very accurate structure\
 based multiple sequence alignments\";\n$MODE{\"3d\
coffee\"}{description}=\" for multiple structure a\
lignments\";\n$MODE{mcoffee} {description}=\" for \
combining alternative multiple sequence alignment \
packages\\n------- into a unique meta-package. The\
 installer will upload several MSA packages and co\
mpile them\\n\n\";\n\n\n&post_process_PG();\nretur\
n;\n}\n\nsub post_process_PG\n  {\n    my $p;\n   \
 \n    %PG=&name2dname (%PG);\n    %MODE=&name2dna\
me(%MODE);\n    foreach $p (keys(%PG)){if ( $PG{$p\
}{type} eq \"compiler\"){$PG{$p}{update_action}=\"\
never\";}}\n    \n  }\n\nsub name2dname\n  {\n    \
my (%L)=(@_);\n    my ($l, $ml);\n    \n    foreac\
h my $pg (keys(%L))\n      {\n	$l=length ($pg);\n	\
if ( $l>$ml){$ml=$l;}\n      }\n    $ml+=1;\n    f\
oreach my $pg (keys(%L))\n      {\n	my $name;\n	$l\
=$ml-length ($pg);\n	$name=$pg;\n	for ( $b=0; $b<$\
l; $b++)\n	  {\n	    $name .=\" \";\n	  }\n	$L{$pg\
}{dname}=$name;\n      }\n    return %L;\n  }\n\ns\
ub env_file2putenv\n  {\n    my $f=@_[0];\n    my \
$F=new FileHandle;\n    my $n;\n    \n    open ($F\
, \"$f\");\n    while (<$F>)\n      {\n	my $line=$\
_;\n	my($var, $value)=($_=~/(\\S+)\\=(\\S*)/);\n	$\
ENV{$var}=$value;\n	$ENV_SET{$var}=1;\n	$n++;\n   \
   }\n    close ($F);\n    return $n;\n  }\n\nsub \
replace_line_in_file\n  {\n    my ($file, $wordin,\
 $wordout)=@_;\n    my $O=new FileHandle;\n    my \
$I=new FileHandle;\n    my $l;\n    if (!-e $file)\
{return;}\n    \n    system (\"mv $file $file.old\\
");\n    open ($O, \">$file\");\n    open ($I, \"$\
file.old\");\n    while (<$I>)\n      {\n	$l=$_;\n\
	if (!($l=~/$wordin/)){print $O \"$l\";}\n	elsif (\
 $wordout ne \"\"){$l=~s/$wordin/$wordout/g;print \
$O \"$l\";}\n      }\n    close ($O);\n    close (\
$I);\n    return;\n  }\n\nsub add_C_libraries\n  {\
\n   my ($file,$first,@list)=@_;\n   \n    my $O=n\
ew FileHandle;\n    my $I=new FileHandle;\n    my \
($l,$anchor);\n    if (!-e $file){return;}\n   \n \
   $anchor=\"#include <$first>\";\n	 \n    system \
(\"mv $file $file.old\");\n    open ($O, \">$file\\
");\n    open ($I, \"$file.old\");\n    while (<$I\
>)\n      {\n	$l=$_;\n	print $O \"$l\";\n	if (!($l\
=~/$anchor/))\n	   {\n	    \n	    foreach my $lib \
(@list)\n	       {\n                  print $O \"#\
include <$lib>\\n\";\n	       }\n           }\n   \
   }\n    close ($O);\n    close ($I);\n    return\
;\n    }\n","use Env;\nuse Cwd;\n@suffix=(\"tmp\",\
 \"temp\", \"cache\", \"t_coffee\", \"core\", \"tc\
offee\");\n\nif ($#ARGV==-1)\n  {\n    print \"cle\
an_cache.pl -file <file to add in -dir> -dir=<dir>\
 -size=<value in Mb>\\n0: unlimited -1 always.\\nW\
ill only clean directories matching:[\";\n    fore\
ach $k(@suffix){print \"*$k* \";}\n    print \"]\\\
n\";\n    exit (EXIT_FAILURE);\n  }\n\n$cl=join (\\
" \",@ARGV);\nif (($cl=~/\\-no_action/))\n  {\n   \
 exit (EXIT_SUCCESS);\n  }\n\nif (($cl=~/\\-debug/\
))\n  {\n    $DEBUG=1;\n  }\nelse\n  {\n    $DEBUG\
=0;\n  }\n\nif (($cl=~/\\-dir=(\\S+)/))\n  {\n    \
$dir=$1;\n  }\nelse\n  {\n    $dir=\"./\";\n  }\n\\
nif ($cl=~/\\-file=(\\S+)/)\n  {\n    $file=$1;\n \
 }\nelse\n  {\n    $file=0;\n  }\n\nif ($cl=~/\\-s\
ize=(\\S+)/)\n  {\n    $max_size=$1;\n  }\nelse\n \
 {\n    $max_size=0;#unlimited\n  }\nif ($cl=~/\\-\
force/)\n  {\n    $force=1;\n  }\nelse\n  {\n    $\
force=0;\n  }\n\nif ($cl=~/\\-age=(\\S+)/)\n  {\n \
   $max_age=$1;\n  }\nelse\n  {\n    $max_age=0;#u\
nlimited\n  }\n\n$max_size*=1000000;\nif ( ! -d $d\
ir)\n  {\n    print STDERR \"\\nCannot process $di\
r: does not exist \\n\";\n    exit (EXIT_FAILURE);\
\n  }\n\nif ( !($dir=~/^\\//))\n  {\n    $base=cwd\
();\n    $dir=\"$base/$dir\";\n  }\n\n$proceed=0;\\
nforeach $s (@suffix)\n  {\n    \n    if (($dir=~/\
$s/)){$proceed=1;}\n    $s=uc ($s);\n    if (($dir\
=~/$s/)){$proceed=1;}\n  }\nif ( $proceed==0)\n  {\
\n    print STDERR \"Clean_cache.pl can only clean\
 directories whose absolute path name contains the\
 following strings:\";\n    foreach $w (@suffix) {\
print STDERR \"$w \";$w=lc($w); print STDERR \"$w \
\";}\n    print STDERR \"\\nCannot process $dir\\n\
\";\n    exit (EXIT_FAILURE);\n  }\n\n$name_file=\\
"$dir/name_file.txt\";\n$size_file=\"$dir/size_fil\
e.txt\";\nif ( $force){&create_ref_file ($dir,$nam\
e_file,$size_file);}\nif ($file){&add_file ($dir, \
$name_file, $size_file, $file);}\n&clean_dir ($dir\
, $name_file, $size_file, $max_size,$max_age);\nex\
it (EXIT_SUCCESS);\n\nsub clean_dir \n  {\n    my \
($dir, $name_file, $size_file, $max_size, $max_age\
)=@_;\n    my ($tot_size, $size, $f, $s);\n\n  \n \
   $tot_size=&get_tot_size ($dir, $name_file, $siz\
e_file);\n\n    if ( $tot_size<=$max_size){return \
;}\n    else {$max_size/=2;}\n    \n    #recreate \
the name file in case some temprary files have not\
 been properly registered\n    &create_ref_file ($\
dir, $name_file, $size_file, $max_age);\n  \n    $\
new_name_file=&vtmpnam();\n    open (R, \"$name_fi\
le\");\n    open (W, \">$new_name_file\");\n    wh\
ile (<R>)\n      {\n	my $line=$_;\n	\n	($f, $s)=($\
line=~/(\\S+) (\\S+)/);\n	if ( !($f=~/\\S/)){next;\
}\n	\n	elsif ($max_size && $tot_size>=$max_size &&\
 !($f=~/name_file/))\n	  {\n	    remove ( \"$dir/$\
f\");\n	    $tot_size-=$s;\n	  }\n	elsif ( $max_ag\
e && -M(\"$dir/$f\")>=$max_age)\n	  {\n	    remove\
 ( \"$dir/$f\");\n	    $tot_size-=$s;\n	  }\n	else\
\n	  {\n	    print W \"$f $s\\n\";\n	  }\n      }\\
n    close (R);\n    close (W);\n    open (F, \">$\
size_file\");\n    print F \"$tot_size\";\n    if \
( -e $new_name_file){`mv $new_name_file $name_file\
`;}\n    close (F);\n  }\nsub get_tot_size\n  {\n \
   my ($dir, $name_file, $size_file)=@_;\n    my $\
size;\n    \n    if ( !-d $dir){return 0;}\n    if\
 ( !-e $name_file)\n      {\n	\n	&create_ref_file \
($dir, $name_file, $size_file);\n      }\n    open\
 (F, \"$size_file\");\n    $size=<F>;\n    close (\
F);\n    chomp ($size);\n    return $size;\n  }\ns\
ub size \n  {\n    my $f=@_[0];\n\n    if ( !-d $f\
){return -s($f);}\n    else {return &dir2size($f);\
}\n  }\nsub dir2size\n  {\n    my $d=@_[0];\n    m\
y ($s, $f);\n    \n    if ( !-d $d) {return 0;}\n \
   \n    foreach $f (&dir2list ($d))\n      {\n	if\
 ( -d $f){$s+=&dir2size (\"$d/$f\");}\n	else {$s+=\
 -s \"$dir/$f\";}\n      }\n    return $s;\n  }\n\\
nsub remove \n  {\n    my $file=@_[0];\n    my ($f\
);\n    \n    debug_print( \"--- $file ---\\n\");\\
n    if (($file eq \".\") || ($file eq \"..\") || \
($file=~/\\*/)){return EXIT_FAILURE;}\n    elsif (\
 !-d $file)\n      {\n	debug_print (\"unlink $file\
\\n\");\n	if (-e $file){unlink ($file);}\n      }\\
n    elsif ( -d $file)\n      {\n	debug_print (\"+\
+++++++ $file +++++++\\n\");\n	foreach $f (&dir2li\
st($file))\n	  {\n	    &remove (\"$file/$f\");\n	 \
 }\n	debug_print (\"rmdir $file\\n\");\n	rmdir $fi\
le;\n      }\n    else\n      {\n	debug_print (\"?\
???????? $file ????????\\n\");\n      }\n    retur\
n EXIT_SUCCESS;\n  }\n\nsub dir2list\n  {\n    my \
$dir=@_[0];\n    my (@list1, @list2,@list3, $l);\n\
\n    opendir (DIR,$dir);\n    @list1=readdir (DIR\
);\n    closedir (DIR);\n    \n    foreach $l (@li\
st1)\n      {\n	if ( $l ne \".\" && $l ne \"..\"){\
@list2=(@list2, $l);}\n      }\n    @list3 = sort \
{ (-M \"$dir/$list2[$b]\") <=> (-M \"$dir/$list2[$\
a]\")} @list2;\n    return @list3;\n    \n  }\n\ns\
ub debug_print\n  {\n    \n    if ($DEBUG==1){prin\
t @_;}\n    \n  }\nsub create_ref_file\n  {\n    m\
y ($dir,$name_file,$size_file)=@_;\n    my ($f, $s\
, $tot_size, @l);\n    \n    if ( !-d $dir){return\
;}\n    \n    @l=&dir2list ($dir);\n    open (F, \\
">$name_file\");\n    foreach $f (@l)\n      {\n	$\
s=&size(\"$dir/$f\");\n	$tot_size+=$s;\n	print F \\
"$f $s\\n\";\n      }\n    &myecho ($tot_size, \">\
$size_file\");\n    close (F);\n  }\nsub add_file \
\n  {\n    my ($dir,$name_file,$size_file,$file)=@\
_;\n    my ($s, $tot_size);\n    \n    if ( !-d $d\
ir)   {return;}\n    if ( !-e \"$dir/$file\" ) {re\
turn;}\n    if ( !-e $name_file){&create_ref_file \
($dir,$name_file,$size_file);}\n					    \n    $s=\
&size(\"$dir/$file\");\n    open (F, \">>$name_fil\
e\");\n    print F \"$file\\n\";\n    close (F);\n\
\n    $tot_size=&get_tot_size ($dir,$name_file,$si\
ze_file);\n    $tot_size+=$s;\n    &myecho ($tot_s\
ize, \">$size_file\");\n    \n  }\n	\nsub myecho\n\
  {\n    my ($string, $file)=@_;\n    open (ECHO, \
$file) || die;\n    print ECHO \"$string\";\n    c\
lose (ECHO);\n  }\n    \n		\n	\nsub vtmpnam\n  {\n\
    my $tmp_file_name;\n    $tmp_name_counter++;\n\
    $tmp_file_name=\"tmp_file_for_clean_cache_pdb$\
$.$tmp_name_counter\";\n    $tmp_file_list[$ntmp_f\
ile++]=$tmp_file_name;\n    if ( -e $tmp_file_name\
) {return &vtmpnam ();}\n    else {return $tmp_fil\
e_name;}\n  }\n","\nmy $address=\"http://www.tcoff\
ee.org/Data/Datasets/NatureProtocolsDataset.tar.gz\
\";\nmy $out=\"NatureProtocolsDataset.tar.gz\";\n&\
url2file ($address,$out);\n\nif ( -e $out)\n  {\n \
   \n    system (\"gunzip NatureProtocolsDataset.t\
ar.gz\");\n    system (\"tar -xvf NatureProtocolsD\
ataset.tar\");\n  	system (\"rm -rf NatureProtocol\
sDataset.tar\");  \n    print \"Your Data Set is i\
n the Folder 'NatureProtocolsDataset'\\n\";\n  }\n\
else \n  {\n    print \"Could not Download Dataset\
 --- Web site may be down -- Try again later\\n\";\
\n  }\n\n\n\n\nsub url2file\n{\n    my ($address, \
$out, $wget_arg, $curl_arg)=(@_);\n    my ($pg, $f\
lag, $r, $arg, $count);\n    \n    if (!$CONFIGURA\
TION){&check_configuration (\"wget\", \"INTERNET\"\
, \"gzip\");$CONFIGURATION=1;}\n    \n    if (&pg_\
is_installed (\"wget\"))   {$pg=\"wget\"; $flag=\"\
-O\";$arg=$wget_arg;}\n    elsif (&pg_is_installed\
 (\"curl\")){$pg=\"curl\"; $flag=\"-o\";$arg=$curl\
_arg;}\n    return system (\"$pg $address $flag $o\
ut>/dev/null 2>/dev/null\");\n\n}\n\nsub pg_is_ins\
talled\n  {\n    my @ml=@_;\n    my $r, $p, $m;\n \
   my $supported=0;\n    \n    my $p=shift (@ml);\\
n    if ($p=~/::/)\n      {\n	if (system (\"perl -\
M$p -e 1\")==$EXIT_SUCCESS){return 1;}\n	else {ret\
urn 0;}\n      }\n    else\n      {\n	$r=`which $p\
 2>/dev/null`;\n	if ($r eq \"\"){return 0;}\n	else\
 {return 1;}\n      }\n  }\nsub check_configuratio\
n \n    {\n      my @l=@_;\n      my $v;\n      fo\
reach my $p (@l)\n	{\n	  \n	  if   ( $p eq \"EMAIL\
\")\n	    { \n	      if ( !($EMAIL=~/@/))\n		{\n		\
  exit (EXIT_FAILURE);\n		}\n	    }\n	  elsif( $p \
eq \"INTERNET\")\n	    {\n	      if ( !&check_inte\
rnet_connection())\n		{\n		  exit (EXIT_FAILURE);\\
n		}\n	    }\n	  elsif( $p eq \"wget\")\n	    {\n	\
      if (!&pg_is_installed (\"wget\") && !&pg_is_\
installed (\"curl\"))\n		{\n		  exit (EXIT_FAILURE\
);\n		}\n	    }\n	  elsif( !(&pg_is_installed ($p)\
))\n	    {\n	      exit (EXIT_FAILURE);\n	    }\n	\
}\n      return 1;\n    }\nsub check_internet_conn\
ection\n  {\n    my $internet;\n    my $tmp;\n    \
&check_configuration ( \"wget\"); \n    \n    $tmp\
=&vtmpnam ();\n    \n    if     (&pg_is_installed \
   (\"wget\")){`wget www.google.com -O$tmp >/dev/n\
ull 2>/dev/null`;}\n    elsif  (&pg_is_installed  \
  (\"curl\")){`curl www.google.com -o$tmp >/dev/nu\
ll 2>/dev/null`;}\n    \n    if ( !-e $tmp || -s $\
tmp < 10){$internet=0;}\n    else {$internet=1;}\n\
    if (-e $tmp){unlink $tmp;}\n\n    return $inte\
rnet;\n  }\n\nsub vtmpnam\n      {\n	my $r=rand(10\
0000);\n	my $f=\"file.$r.$$\";\n	while (-e $f)\n	 \
 {\n	    $f=vtmpnam();\n	  }\n	push (@TMPFILE_LIST\
, $f);\n	return $f;\n      }\n\n","\n$t_coffee=\"t\
_coffee\";\n\nforeach $value ( @ARGV)\n  {\n    $s\
eq_file=$seq_file.\" \".$value;\n  }\n\n$name=$ARG\
V[0];\n$name=~s/\\.[^\\.]*$//;\n$lib_name=\"$name.\
mocca_lib\";\n$type=`t_coffee $seq_file -get_type \
-quiet`;\nchop ($type);\n\nif ( $type eq \"PROTEIN\
\"){$lib_mode=\"lalign_rs_s_pair -lalign_n_top 20\\
";}\nelsif ( $type eq\"DNA\"){$lib_mode=\"lalign_r\
s_s_dna_pair -lalign_n_top 40\";}\n\nif ( !(-e $li\
b_name))\n  {\n	  \n  $command=\"$t_coffee -mocca \
-seq_weight=no -cosmetic_penalty=0 -mocca_interact\
ive -in $lib_mode -out_lib $lib_name -infile $seq_\
file\";\n  \n  }\nelsif ( (-e $lib_name))\n  {\n  \
$command=\"$t_coffee -mocca -seq_weight=no -cosmet\
ic_penalty=0 -mocca_interactive -in $lib_name -inf\
ile $seq_file\";\n  \n  }\n\nsystem ($command);\n\\
nexit;\n\n","my $WSDL = 'http://www.ebi.ac.uk/Tool\
s/webservices/wsdl/WSDaliLite.wsdl';\n\nuse SOAP::\
Lite;\nuse Data::Dumper;\nuse Getopt::Long qw(:con\
fig no_ignore_case bundling);\nuse File::Basename;\
\n\nmy $checkInterval = 5;\n\nmy %params=(\n	    '\
async' => '1', # Use async mode and simulate sync \
mode in client\n	    );\nGetOptions(\n    'pdb1=s'\
     => \\$params{'sequence1'},\n    'chainid1=s' \
=> \\$params{'chainid1'},\n    'pdb2=s'     => \\$\
params{'sequence2'},\n    'chainid2=s' => \\$param\
s{'chainid2'},\n    \"help|h\"	 => \\$help, # Usag\
e info\n    \"async|a\"	 => \\$async, # Asynchrono\
us submission\n    \"polljob\"	 => \\$polljob, # G\
et results\n    \"status\"	 => \\$status, # Get st\
atus\n    \"jobid|j=s\"  => \\$jobid, # JobId\n   \
 \"email|S=s\"  => \\$params{email}, # E-mail addr\
ess\n    \"trace\"      => \\$trace, # SOAP messag\
es\n    \"sequence=s\" => \\$sequence, # Input PDB\
\n    );\n\nmy $scriptName = basename($0, ());\nif\
($help) {\n    &usage();\n    exit(0);\n}\n\nif($t\
race) {\n    print \"Tracing active\\n\";\n    SOA\
P::Lite->import(+trace => 'debug');\n}\n\nmy $soap\
 = SOAP::Lite\n    ->service($WSDL)\n    ->on_faul\
t(sub {\n        my $soap = shift;\n        my $re\
s = shift;\n        # Throw an exception for all f\
aults\n        if(ref($res) eq '') {\n            \
die($res);\n        } else {\n            die($res\
->faultstring);\n        }\n        return new SOA\
P::SOM;\n    }\n               );\n\nif( !($polljo\
b || $status) &&\n    !( defined($params{'sequence\
1'}) && defined($params{'sequence2'}) )\n    ) {\n\
    print STDERR 'Error: bad option combination', \
\"\\n\";\n    &usage();\n    exit(1);\n}\nelsif($p\
olljob && defined($jobid)) {\n    print \"Getting \
results for job $jobid\\n\";\n    getResults($jobi\
d);\n}\nelsif($status && defined($jobid)) {\n    p\
rint STDERR \"Getting status for job $jobid\\n\";\\
n    my $result = $soap->checkStatus($jobid);\n   \
 print STDOUT \"$result\", \"\\n\";\n    if($resul\
t eq 'DONE') {\n	print STDERR \"To get results: $s\
criptName --polljob --jobid $jobid\\n\";\n    }\n}\
\nelse {\n    if(-f $params{'sequence1'}) {\n	$par\
ams{'sequence1'} = read_file($params{'sequence1'})\
;\n    }\n    if(-f $params{'sequence2'}) {\n	$par\
ams{'sequence2'} = read_file($params{'sequence2'})\
;\n    }\n\n    my $jobid;\n    my $paramsData = S\
OAP::Data->name('params')->type(map=>\\%params);\n\
    # For SOAP::Lite 0.60 and earlier parameters a\
re passed directly\n    if($SOAP::Lite::VERSION eq\
 '0.60' || $SOAP::Lite::VERSION =~ /0\\.[1-5]/) {\\
n        $jobid = $soap->runDaliLite($paramsData);\
\n    }\n    # For SOAP::Lite 0.69 and later param\
eter handling is different, so pass\n    # undef's\
 for templated params, and then pass the formatted\
 args.\n    else {\n        $jobid = $soap->runDal\
iLite(undef,\n				     $paramsData);\n    }\n\n   \
 if (defined($async)) {\n	print STDOUT $jobid, \"\\
\n\";\n        print STDERR \"To check status: $sc\
riptName --status --jobid $jobid\\n\";\n    } else\
 { # Synchronous mode\n        print STDERR \"JobI\
d: $jobid\\n\";\n        sleep 1;\n        getResu\
lts($jobid);\n    }\n}\n\nsub clientPoll($) {\n   \
 my $jobid = shift;\n    my $result = 'PENDING';\n\
    # Check status and wait if not finished\n    #\
print STDERR \"Checking status: $jobid\\n\";\n    \
while($result eq 'RUNNING' || $result eq 'PENDING'\
) {\n        $result = $soap->checkStatus($jobid);\
\n        print STDERR \"$result\\n\";\n        if\
($result eq 'RUNNING' || $result eq 'PENDING') {\n\
            # Wait before polling again.\n        \
    sleep $checkInterval;\n        }\n    }\n}\n\n\
sub getResults($) {\n    $jobid = shift;\n    # Ch\
eck status, and wait if not finished\n    clientPo\
ll($jobid);\n    # Use JobId if output file name i\
s not defined\n    unless(defined($outfile)) {\n  \
      $outfile=$jobid;\n    }\n    # Get list of d\
ata types\n    my $resultTypes = $soap->getResults\
($jobid);\n    # Get the data and write it to a fi\
le\n    if(defined($outformat)) { # Specified data\
 type\n        my $selResultType;\n        foreach\
 my $resultType (@$resultTypes) {\n            if(\
$resultType->{type} eq $outformat) {\n            \
    $selResultType = $resultType;\n            }\n\
        }\n        $res=$soap->poll($jobid, $selRe\
sultType->{type});\n        write_file($outfile.'.\
'.$selResultType->{ext}, $res);\n    } else { # Da\
ta types available\n        # Write a file for eac\
h output type\n        for my $resultType (@$resul\
tTypes){\n            #print \"Getting $resultType\
->{type}\\n\";\n            $res=$soap->poll($jobi\
d, $resultType->{type});\n            write_file($\
outfile.'.'.$resultType->{ext}, $res);\n        }\\
n    }\n}\n\nsub read_file($) {\n    my $filename \
= shift;\n    open(FILE, $filename);\n    my $cont\
ent;\n    my $buffer;\n    while(sysread(FILE, $bu\
ffer, 1024)) {\n	$content.= $buffer;\n    }\n    c\
lose(FILE);\n    return $content;\n}\n\nsub write_\
file($$) {\n    my ($tmp,$entity) = @_;\n    print\
 STDERR \"Creating result file: \".$tmp.\"\\n\";\n\
    unless(open (FILE, \">$tmp\")) {\n	return 0;\n\
    }\n    syswrite(FILE, $entity);\n    close (FI\
LE);\n    return 1;\n}\n\nsub usage {\n    print S\
TDERR <<EOF\nDaliLite\n========\n\nPairwise compar\
ison of protein structures\n\n[Required]\n\n  --pd\
b1                : str  : PDB ID for structure 1\\
n  --pdb2                : str  : PDB ID for struc\
ture 2\n\n[Optional]\n\n  --chain1              : \
str  : Chain identifer in structure 1\n  --chain2 \
             : str  : Chain identifer in structure\
 2\n\n[General]\n\n  -h, --help            :      \
: prints this help text\n  -S, --email           :\
 str  : user email address\n  -a, --async         \
  :      : asynchronous submission\n      --status\
          :      : poll for the status of a job\n \
     --polljob         :      : poll for the resul\
ts of a job\n  -j, --jobid           : str  : jobi\
d for an asynchronous job\n  -O, --outfile        \
 : str  : file name for results (default is jobid)\
\n      --trace	        :      : show SOAP message\
s being interchanged \n\nSynchronous job:\n\n  The\
 results/errors are returned as soon as the job is\
 finished.\n  Usage: $scriptName --email <your\\@e\
mail> [options] pdbFile [--outfile string]\n  Retu\
rns: saves the results to disk\n\nAsynchronous job\
:\n\n  Use this if you want to retrieve the result\
s at a later time. The results \n  are stored for \
up to 24 hours. \n  The asynchronous submission mo\
de is recommended when users are submitting \n  ba\
tch jobs or large database searches	\n  Usage: $sc\
riptName --email <your\\@email> --async [options] \
pdbFile\n  Returns: jobid\n\n  Use the jobid to qu\
ery for the status of the job. \n  Usage: $scriptN\
ame --status --jobid <jobId>\n  Returns: string in\
dicating the status of the job:\n    DONE - job ha\
s finished\n    RUNNING - job is running\n    NOT_\
FOUND - job cannot be found\n    ERROR - the jobs \
has encountered an error\n\n  When done, use the j\
obid to retrieve the status of the job. \n  Usage:\
 $scriptName --polljob --jobid <jobId> [--outfile \
string]\n\n[Help]\n\n  For more detailed help info\
rmation refer to\n  http://www.ebi.ac.uk/DaliLite/\
\nEOF\n;\n}\n","my $WSDL = 'http://www.ebi.ac.uk/T\
ools/webservices/wsdl/WSWUBlast.wsdl';\n\nuse stri\
ct;\nuse SOAP::Lite;\nuse Getopt::Long qw(:config \
no_ignore_case bundling);\nuse File::Basename;\n\n\
my $checkInterval = 15;\n\nmy $numOpts = scalar(@A\
RGV);\nmy ($outfile, $outformat, $help, $async, $p\
olljob, $status, $ids, $jobid, $trace, $sequence);\
\nmy %params= ( # Defaults\n	      'async' => 1, #\
 Force into async mode\n	      'exp' => 10.0, # E-\
value threshold\n	      'numal' => 50, # Maximum n\
umber of alignments\n	      'scores' => 100, # Max\
imum number of scores\n            );\nGetOptions(\
 # Map the options into variables\n    \"program|p\
=s\"     => \\$params{program}, # BLAST program\n \
   \"database|D=s\"    => \\$params{database}, # S\
earch database\n    \"matrix|m=s\"      => \\$para\
ms{matrix}, # Scoring matrix\n    \"exp|E=f\"     \
    => \\$params{exp}, # E-value threshold\n    \"\
echofilter|e\"    => \\$params{echofilter}, # Disp\
lay filtered sequence\n    \"filter|f=s\"      => \
\\$params{filter}, # Low complexity filter name\n \
   \"alignments|b=i\"  => \\$params{numal}, # Numb\
er of alignments\n    \"scores|s=i\"      => \\$pa\
rams{scores}, # Number of scores\n    \"sensitivit\
y|S=s\" => \\$params{sensitivity}, # Search sensit\
ivity\n    \"sort|t=s\"	      => \\$params{sort}, \
# Sort hits by...\n    \"stats|T=s\"       => \\$p\
arams{stats}, # Scoring statistic to use\n    \"st\
rand|d=s\"      => \\$params{strand}, # Strand to \
use in DNA vs. DNA search\n    \"topcombon|c=i\"  \
 => \\$params{topcombon}, # Consistent sets of HSP\
s\n    \"outfile=s\"       => \\$outfile, # Output\
 file\n    \"outformat|o=s\"   => \\$outformat, # \
Output format\n    \"help|h\"	      => \\$help, # \
Usage info\n    \"async|a\"	      => \\$async, # A\
synchronous mode\n    \"polljob\"	      => \\$poll\
job, # Get results\n    \"status\"	      => \\$sta\
tus, # Get job status\n    \"ids\"             => \
\\$ids, # Get ids from result\n    \"jobid|j=s\"  \
     => \\$jobid, # JobId\n    \"email=s\"        \
 => \\$params{email}, # E-mail address\n    \"trac\
e\"           => \\$trace, # SOAP trace\n    \"seq\
uence=s\"      => \\$sequence, # Query sequence\n \
   );\n\nmy $scriptName = basename($0, ());\nif($h\
elp || $numOpts == 0) {\n    &usage();\n    exit(0\
);\n}\n\nif($trace){\n    print STDERR \"Tracing a\
ctive\\n\";\n    SOAP::Lite->import(+trace => 'deb\
ug');\n}\n\nmy $soap = SOAP::Lite\n    ->service($\
WSDL)\n    ->proxy('http://localhost/',\n    #prox\
y => ['http' => 'http://your.proxy.server/'], # HT\
TP proxy\n    timeout => 600, # HTTP connection ti\
meout\n    )\n    ->on_fault(sub { # SOAP fault ha\
ndler\n        my $soap = shift;\n        my $res \
= shift;\n        # Throw an exception for all fau\
lts\n        if(ref($res) eq '') {\n            di\
e($res);\n        } else {\n            die($res->\
faultstring);\n        }\n        return new SOAP:\
:SOM;\n    }\n               );\n\nif( !($polljob \
|| $status || $ids) &&\n    !( defined($ARGV[0]) |\
| defined($sequence) )\n    ) {\n    print STDERR \
'Error: bad option combination', \"\\n\";\n    &us\
age();\n    exit(1);\n}\nelsif($polljob && defined\
($jobid)) {\n    print \"Getting results for job $\
jobid\\n\";\n    getResults($jobid);\n}\nelsif($st\
atus && defined($jobid)) {\n    print STDERR \"Get\
ting status for job $jobid\\n\";\n    my $result =\
 $soap->checkStatus($jobid);\n    print STDOUT \"$\
result\\n\";\n    if($result eq 'DONE') {\n	print \
STDERR \"To get results: $scriptName --polljob --j\
obid $jobid\\n\";\n    }\n}  \nelsif($ids && defin\
ed($jobid)) {\n    print STDERR \"Getting ids from\
 job $jobid\\n\";\n    getIds($jobid);\n}\nelse {\\
n    # Prepare input data\n    my $content;\n    m\
y (@contents) = ();\n    if(-f $ARGV[0] || $ARGV[0\
] eq '-') {	\n	$content={type=>'sequence',content=\
>read_file($ARGV[0])};	\n    }\n    if($sequence) \
{	\n	if(-f $sequence || $sequence eq '-') {	\n	   \
 $content={type=>'sequence',content=>read_file($AR\
GV[0])};	\n	} else {\n	    $content={type=>'sequen\
ce',content=>$sequence};\n	}\n    }\n    push @con\
tents, $content;\n\n    # Submit the job\n    my $\
paramsData = SOAP::Data->name('params')->type(map=\
>\\%params);\n    my $contentData = SOAP::Data->na\
me('content')->value(\\@contents);\n    # For SOAP\
::Lite 0.60 and earlier parameters are passed dire\
ctly\n    if($SOAP::Lite::VERSION eq '0.60' || $SO\
AP::Lite::VERSION =~ /0\\.[1-5]/) {\n        $jobi\
d = $soap->runWUBlast($paramsData, $contentData);\\
n    }\n    # For SOAP::Lite 0.69 and later parame\
ter handling is different, so pass\n    # undef's \
for templated params, and then pass the formatted \
args.\n    else {\n        $jobid = $soap->runWUBl\
ast(undef, undef,\n				   $paramsData, $contentDat\
a);\n    }\n\n    # Asynchronous mode: output jobi\
d and exit.\n    if (defined($async)) {\n	print ST\
DOUT $jobid, \"\\n\";\n        print STDERR \"To c\
heck status: $scriptName --status --jobid $jobid\\\
n\";\n    }\n    # Synchronous mode: try to get re\
sults\n    else {\n        print STDERR \"JobId: $\
jobid\\n\";\n        sleep 1;\n        getResults(\
$jobid);\n    }\n}\n\nsub getIds($) {\n    my $job\
id = shift;\n    my $results = $soap->getIds($jobi\
d);\n    for my $result (@$results){\n	print \"$re\
sult\\n\";\n    }\n}\n\nsub clientPoll($) {\n    m\
y $jobid = shift;\n    my $result = 'PENDING';\n  \
  # Check status and wait if not finished\n    whi\
le($result eq 'RUNNING' || $result eq 'PENDING') {\
\n        $result = $soap->checkStatus($jobid);\n \
       print STDERR \"$result\\n\";\n        if($r\
esult eq 'RUNNING' || $result eq 'PENDING') {\n   \
         # Wait before polling again.\n           \
 sleep $checkInterval;\n        }\n    }\n}\n\nsub\
 getResults($) {\n    my $jobid = shift;\n    my $\
res;\n    # Check status, and wait if not finished\
\n    clientPoll($jobid);\n    # Use JobId if outp\
ut file name is not defined\n    unless(defined($o\
utfile)) {\n        $outfile=$jobid;\n    }\n    #\
 Get list of data types\n    my $resultTypes = $so\
ap->getResults($jobid);\n    # Get the data and wr\
ite it to a file\n    if(defined($outformat)) { # \
Specified data type\n	if($outformat eq 'xml') {$ou\
tformat = 'toolxml';}\n	if($outformat eq 'txt') {$\
outformat = 'tooloutput';}\n        my $selResultT\
ype;\n        foreach my $resultType (@$resultType\
s) {\n            if($resultType->{type} eq $outfo\
rmat) {\n                $selResultType = $resultT\
ype;\n            }\n        }\n        $res=$soap\
->poll($jobid, $selResultType->{type});\n	if($outf\
ile eq '-') {\n	     write_file($outfile, $res);\n\
	} else {\n	    write_file($outfile.'.'.$selResult\
Type->{ext}, $res);\n	}\n    } else { # Data types\
 available\n        # Write a file for each output\
 type\n        for my $resultType (@$resultTypes){\
\n            #print STDERR \"Getting $resultType-\
>{type}\\n\";\n            $res=$soap->poll($jobid\
, $resultType->{type});\n	    if($outfile eq '-') \
{\n		write_file($outfile, $res);\n	    } else {\n	\
	write_file($outfile.'.'.$resultType->{ext}, $res)\
;\n	    }\n        }\n    }\n}\n\nsub read_file($)\
 {\n    my $filename = shift;\n    my ($content, $\
buffer);\n    if($filename eq '-') {\n	while(sysre\
ad(STDIN, $buffer, 1024)) {\n	    $content .= $buf\
fer;\n	}\n    }\n    else { # File\n	open(FILE, $f\
ilename) or die \"Error: unable to open input file\
\";\n	while(sysread(FILE, $buffer, 1024)) {\n	    \
$content .= $buffer;\n	}\n	close(FILE);\n    }\n  \
  return $content;\n}\n\nsub write_file($$) {\n   \
 my ($filename, $data) = @_;\n    print STDERR 'Cr\
eating result file: ' . $filename . \"\\n\";\n    \
if($filename eq '-') {\n	print STDOUT $data;\n    \
}\n    else {\n	open(FILE, \">$filename\") or die \
\"Error: unable to open output file\";\n	syswrite(\
FILE, $data);\n	close(FILE);\n    }\n}\n\nsub usag\
e {\n    print STDERR <<EOF\nWU-BLAST\n========\n\\
nRapid sequence database search programs utilizing\
 the BLAST algorithm.\n   \n[Required]\n\n      --\
email       : str  : user email address \n  -p, --\
program	    : str  : BLAST program to use: blastn,\
 blastp, blastx, \n                             tb\
lastn or tblastx\n  -D, --database    : str  : dat\
abase to search\n  seqFile           : file : quer\
y sequence data file (\"-\" for STDIN)\n\n[Optiona\
l]\n\n  -m, --matrix	    : str  : scoring matrix\n\
  -E, --exp	    : real : 0<E<= 1000. Statistical s\
ignificance threshold\n                           \
  for reporting database sequence matches.\n  -e, \
--echofilter  :      : display the filtered query \
sequence in the output\n  -f, --filter	    : str  \
: activates filtering of the query sequence\n  -b,\
 --alignments  : int  : number of alignments to be\
 reported\n  -s, --scores	    : int  : number of s\
cores to be reported\n  -S, --sensitivity : str  :\
\n  -t, --sort	    : str  :\n  -T, --stats       :\
 str  :\n  -d, --strand      : str  : DNA strand t\
o search with in DNA vs. DNA searches \n  -c, --to\
pcombon   :      :\n\n[General]	\n\n  -h, --help  \
     :      : prints this help text\n  -a, --async\
      :      : forces to make an asynchronous quer\
y\n      --status     :      : poll for the status\
 of a job\n      --polljob    :      : poll for th\
e results of a job\n  -j, --jobid      : str  : jo\
bid that was returned when an asynchronous job \n \
                           was submitted.\n  -O, -\
-outfile    : str  : name of the file results shou\
ld be written to \n                            (de\
fault is based on the jobid; \"-\" for STDOUT)\n  \
-o, --outformat  : str  : txt or xml output (no fi\
le is written)\n      --trace	   :      : show SOA\
P messages being interchanged \n\nSynchronous job:\
\n\n  The results/errors are returned as soon as t\
he job is finished.\n  Usage: $scriptName --email \
<your\\@email> [options...] seqFile\n  Returns: sa\
ves the results to disk\n\nAsynchronous job:\n\n  \
Use this if you want to retrieve the results at a \
later time. The results \n  are stored for up to 2\
4 hours. \n  The asynchronous submission mode is r\
ecommended when users are submitting \n  batch job\
s or large database searches	\n  Usage: $scriptNam\
e --async --email <your\\@email> [options...] seqF\
ile\n  Returns : jobid\n\n  Use the jobid to query\
 for the status of the job. \n  Usage: $scriptName\
 --status --jobid <jobId>\n  Returns : string indi\
cating the status of the job:\n    DONE - job has \
finished\n    RUNNING - job is running\n    NOT_FO\
UND - job cannot be found\n    ERROR - the jobs ha\
s encountered an error\n\n  When done, use the job\
id to retrieve the status of the job. \n  Usage: $\
scriptName --polljob --jobid <jobId> [--outfile st\
ring]\n  Returns: saves the results to disk\n\n[He\
lp]\n\nFor more detailed help information refer to\
 \nhttp://www.ebi.ac.uk/blast2/WU-Blast2_Help_fram\
e.html\n \nEOF\n;\n}\n","\nmy $WSDL = 'http://www.\
ebi.ac.uk/Tools/webservices/wsdl/WSBlastpgp.wsdl';\
\n\nuse SOAP::Lite;\nuse Getopt::Long qw(:config n\
o_ignore_case bundling);\nuse File::Basename;\n\nm\
y $checkInterval = 15;\n\nmy %params=(\n	    'asyn\
c' => '1', # Use async mode and simulate sync mode\
 in client\n	    );\nGetOptions(\n    \"mode=s\"  \
         => \\$params{mode}, # Search mode: PSI-Bl\
ast or PHI-Blast\n    \"database|d=s\"     => \\$p\
arams{database}, # Database to search\n    \"matri\
x|M=s\"       => \\$params{matrix},# Scoring maxtr\
ix\n    \"exp|e=f\"          => \\$params{exp}, # \
E-value\n    \"expmulti|h=f\"     => \\$params{exp\
multi}, # E-value\n    \"filter|F=s\"       => \\$\
params{filter}, # Low complexity filter\n    \"dro\
poff|X=i\"      => \\$params{dropoff}, # Dropoff s\
core\n    \"finaldropoff|Z=i\" => \\$params{finald\
ropoff}, # Final dropoff score\n    \"scores|v=i\"\
       => \\$params{scores}, # Max number of score\
s\n    \"align=i\"          => \\$params{align}, #\
 Alignment view\n    \"startregion|S=i\"  => \\$pa\
rams{startregion}, # Start of region in query\n   \
 \"endregion|H=i\"    => \\$params{endregion}, # E\
nd of region in query\n    \"maxpasses|j=i\"    =>\
 \\$params{maxpasses}, # Number of PSI iterations\\
n    \"opengap|G=i\"      => \\$params{opengap}, #\
 Gap open penalty\n    \"extendgap|E=i\"    => \\$\
params{extendgap}, # Gap extension penalty\n    \"\
pattern=s\"        => \\$params{pattern}, # PHI-BL\
AST pattern\n    \"usagemode|p=s\"    => \\$params\
{usagemode}, # PHI-BLAST program\n    \"appxml=s\"\
         => \\$params{appxml}, # Application XML\n\
    \"sequence=s\"       => \\$sequence, # Query s\
equence\n    \"help\"	       => \\$help, # Usage i\
nfo\n    \"polljob\"	       => \\$polljob, # Get r\
esults\n    \"status\"	       => \\$status, # Get \
status\n    \"ids\"      	       => \\$ids, # Get \
ids from result\n    \"jobid=s\"          => \\$jo\
bid, # JobId\n    \"outfile=s\"        => \\$outfi\
le, # Output filename\n    \"outformat|o=s\"    =>\
 \\$outformat, # Output file format\n    \"async|a\
\"	       => \\$async, # Async submission\n    \"e\
mail=s\"          => \\$params{email}, # User e-ma\
il address\n    \"trace\"            => \\$trace, \
# Show SOAP messages\n    );\n\nmy $scriptName = b\
asename($0, ());\nif($help) {\n    &usage();\n    \
exit(0);\n}\n\nif ($trace){\n    print \"Tracing a\
ctive\\n\";\n    SOAP::Lite->import(+trace => 'deb\
ug');\n}\n\nmy $soap = SOAP::Lite\n    ->service($\
WSDL)\n    ->on_fault(sub {\n        my $soap = sh\
ift;\n        my $res = shift;\n        # Throw an\
 exception for all faults\n        if(ref($res) eq\
 '') {\n            die($res);\n        } else {\n\
            die($res->faultstring);\n        }\n  \
      return new SOAP::SOM;\n    }\n              \
 );\n\nif( !($polljob || $status || $ids) &&\n    \
!( (defined($ARGV[0]) && -f $ARGV[0]) || defined($\
sequence) )\n    ) {\n    print STDERR 'Error: bad\
 option combination', \"\\n\";\n    &usage();\n   \
 exit(1);\n}\nelsif($polljob && defined($jobid)) {\
\n    print \"Getting results for job $jobid\\n\";\
\n    getResults($jobid);\n}\nelsif($status && def\
ined($jobid)) {\n    print STDERR \"Getting status\
 for job $jobid\\n\";\n    my $result = $soap->che\
ckStatus($jobid);\n    print STDOUT $result, \"\\n\
\";\n    if($result eq 'DONE') {\n	print STDERR \"\
To get results: $scriptName --polljob --jobid $job\
id\\n\";\n    }\n}  \nelsif($ids && defined($jobid\
)) {\n    print STDERR \"Getting ids from job $job\
id\\n\";\n    getIds($jobid);\n}\nelse {\n    if(-\
f $ARGV[0]) {	\n	$content={type=>'sequence', conte\
nt=>read_file($ARGV[0])};	\n    }\n    if($sequenc\
e) {	\n	if(-f $sequence) {\n	    $content={type=>'\
sequence', content=>read_file($sequence)};	\n	} el\
se {\n	    $content={type=>'sequence', content=>$s\
equence};\n	}\n    }\n    push @content, $content;\
\n\n    my $jobid;\n    my $paramsData = SOAP::Dat\
a->name('params')->type(map=>\\%params);\n    my $\
contentData = SOAP::Data->name('content')->value(\\
\@content);\n    # For SOAP::Lite 0.60 and earlier\
 parameters are passed directly\n    if($SOAP::Lit\
e::VERSION eq '0.60' || $SOAP::Lite::VERSION =~ /0\
\\.[1-5]/) {\n        $jobid = $soap->runBlastpgp(\
$paramsData, $contentData);\n    }\n    # For SOAP\
::Lite 0.69 and later parameter handling is differ\
ent, so pass\n    # undef's for templated params, \
and then pass the formatted args.\n    else {\n   \
     $jobid = $soap->runBlastpgp(undef, undef,\n		\
		    $paramsData, $contentData);\n    }\n\n    if\
 (defined($async)) {\n	print STDOUT $jobid, \"\\n\\
";\n        print STDERR \"To check status: $scrip\
tName --status --jobid $jobid\\n\";\n    } else { \
# Synchronous mode\n        print STDERR \"JobId: \
$jobid\\n\";\n        sleep 1;\n        getResults\
($jobid);\n    }\n}\n\nsub getIds($) {\n    $jobid\
 = shift;\n    my $results = $soap->getIds($jobid)\
;\n    for $result (@$results){\n	print \"$result\\
\n\";\n    }\n}\n\nsub clientPoll($) {\n    my $jo\
bid = shift;\n    my $result = 'PENDING';\n    # C\
heck status and wait if not finished\n    #print S\
TDERR \"Checking status: $jobid\\n\";\n    while($\
result eq 'RUNNING' || $result eq 'PENDING') {\n  \
      $result = $soap->checkStatus($jobid);\n     \
   print STDERR \"$result\\n\";\n        if($resul\
t eq 'RUNNING' || $result eq 'PENDING') {\n       \
     # Wait before polling again.\n            sle\
ep $checkInterval;\n        }\n    }\n}\n\nsub get\
Results($) {\n    $jobid = shift;\n    # Check sta\
tus, and wait if not finished\n    clientPoll($job\
id);\n    # Use JobId if output file name is not d\
efined\n    unless(defined($outfile)) {\n        $\
outfile=$jobid;\n    }\n    # Get list of data typ\
es\n    my $resultTypes = $soap->getResults($jobid\
);\n    # Get the data and write it to a file\n   \
 if(defined($outformat)) { # Specified data type\n\
        my $selResultType;\n        foreach my $re\
sultType (@$resultTypes) {\n            if($result\
Type->{type} eq $outformat) {\n                $se\
lResultType = $resultType;\n            }\n       \
 }\n        $res=$soap->poll($jobid, $selResultTyp\
e->{type});\n        write_file($outfile.'.'.$selR\
esultType->{ext}, $res);\n    } else { # Data type\
s available\n        # Write a file for each outpu\
t type\n        for my $resultType (@$resultTypes)\
{\n            #print \"Getting $resultType->{type\
}\\n\";\n            $res=$soap->poll($jobid, $res\
ultType->{type});\n            write_file($outfile\
.'.'.$resultType->{ext}, $res);\n        }\n    }\\
n}\n\nsub read_file($) {\n    my $filename = shift\
;\n    open(FILE, $filename);\n    my $content;\n \
   my $buffer;\n    while(sysread(FILE, $buffer, 1\
024)) {\n	$content.= $buffer;\n    }\n    close(FI\
LE);  \n    return $content;\n}\n\nsub write_file(\
$$) {\n    my ($tmp,$entity) = @_;\n    print STDE\
RR \"Creating result file: \".$tmp.\"\\n\";\n    u\
nless(open (FILE, \">$tmp\")) {\n	return 0;\n    }\
\n    syswrite(FILE, $entity);\n    close (FILE);\\
n    return 1;\n}\n\nsub usage {\n    print STDERR\
 <<EOF\nBlastpgp\n========\n   \nThe blastpgp prog\
ram implements the PSI-BLAST and PHI-BLAST variati\
ons\nof NCBI BLAST.\n\nFor more detailed help info\
rmation refer to\nhttp://www.ebi.ac.uk/blastpgp/bl\
astpsi_help_frame.html\n \nBlastpgp specific optio\
ns:\n\n[Required]\n\n      --mode            : str\
  : search mode to use: PSI-Blast or PHI-Blast\n  \
-d, --database        : str  : protein database to\
 search\n  seqFile               : file : query se\
quence\n\n[Optional]\n\n  -M, --matrix          : \
str  : scoring matrix\n  -e, --exp             : r\
eal : Expectation value\n  -h, --expmulti        :\
 real : threshold (multipass model)\n  -F, --filte\
r          : str  : filter query sequence with SEG\
 [T,F]\n  -m, --align           : int  : alignment\
 view option:\n                                 0 \
- pairwise, 1 - M/S identities,\n                 \
                2 - M/S non-identities, 3 - Flat i\
dentities,\n                                 4 - F\
lat non-identities\n  -G, --opengap         : int \
 : cost to open a gap\n  -E, --extendgap       : i\
nt  : cost to extend a gap\n  -g, --gapalign      \
  : str  : Gapped [T,F]\n  -v, --scores          :\
 int  : number of scores to be reported\n  -j, --m\
axpasses       : int  : number of iterations\n  -X\
, --dropoff         : int  : Dropoff score\n  -Z, \
--finaldropoff    : int  : Dropoff for final align\
ment\n  -S, --startregion     : int  : Start of re\
quired region in query\n  -H, --endregion       : \
int  : End of required region in query\n  -k, --pa\
ttern         : str  : Hit File (PHI-BLAST only)\n\
  -p, --usagemode       : str  : Program option (P\
HI-BLAST only):\n                                 \
blastpgp, patseedp, seedp\n\n[General]\n\n      --\
help            :      : prints this help text\n  \
-a, --async           :      : forces to make an a\
synchronous query\n      --status          :      \
: poll for the status of a job\n      --polljob   \
      :      : poll for the results of a job\n    \
  --jobid           : str  : jobid of an asynchron\
ous job\n      --ids             :      : get hit \
identifiers for result \n  -O, --outfile         :\
 str  : name of the file results should be written\
 to\n                                 (default is \
based on the jobid)\n  -o, --outformat       : str\
  : txt or xml output (no file is written)\n      \
--trace           :      : show SOAP messages bein\
g interchanged\n\nSynchronous job:\n\n  The result\
s/errors are returned as soon as the job is finish\
ed.\n  Usage: blastpgp.pl --email <your@email> [op\
tions...] seqfile\n  Returns: saves the results to\
 disk\n\nAsynchronous job:\n\n  Use this if you wa\
nt to retrieve the results at a later time. The re\
sults\n  are stored for up to 24 hours.\n  The asy\
nchronous submission mode is recommended when user\
s are submitting\n  batch jobs or large database s\
earches\n  Usage: blastpgp.pl --email <your@email>\
 --async [options...] seqFile\n  Returns: jobid\n\\
n  Use the jobid to query for the status of the jo\
b.\n  Usage: blastpgp.pl --status --jobid <jobId>\\
n  Returns: string indicating the status of the jo\
b\n    DONE - job has finished\n    RUNNING - job \
is running\n    NOT_FOUND - job cannot be found\n \
   ERROR - the jobs has encountered an error\n\n  \
When done, use the jobid to retrieve the results o\
f the job.\n  Usage: blastpgp.pl --polljob --jobid\
 <jobId> [--outfile <fileName>]\n  Returns: saves \
the results to disk\nEOF\n;\n}\n","\n=head1 NAME\n\
\nncbiblast_lwp.pl\n\n=head1 DESCRIPTION\n\nNCBI B\
LAST (REST) web service Perl client using L<LWP>.\\
n\nTested with:\n\n=over\n\n=item *\nL<LWP> 5.79, \
L<XML::Simple> 2.12 and Perl 5.8.3\n\n=item *\nL<L\
WP> 5.808, L<XML::Simple> 2.18 and Perl 5.8.8 (Ubu\
ntu 8.04 LTS)\n\n=item *\nL<LWP> 5.834, L<XML::Sim\
ple> 2.18 and Perl 5.10.1 (Ubuntu 10.04 LTS)\n\n=i\
tem *\nL<LWP> 6.03, L<XML::Simple> 2.18 and Perl 5\
.14.2 (Ubuntu 12.04 LTS)\n\n=back\n\nFor further i\
nformation see:\n\n=over\n\n=item *\nL<http://www.\
ebi.ac.uk/Tools/webservices/services/sss/ncbi_blas\
t_rest>\n\n=item *\nL<http://www.ebi.ac.uk/Tools/w\
ebservices/tutorials/perl>\n\n=back\n\n=head1 LICE\
NSE\n\nCopyright 2012-2013 EMBL - European Bioinfo\
rmatics Institute\n\nLicensed under the Apache Lic\
ense, Version 2.0 (the \"License\");\nyou may not \
use this file except in compliance with the Licens\
e.\nYou may obtain a copy of the License at\n\n   \
 http://www.apache.org/licenses/LICENSE-2.0\n\nUnl\
ess required by applicable law or agreed to in wri\
ting, software\ndistributed under the License is d\
istributed on an \"AS IS\" BASIS,\nWITHOUT WARRANT\
IES OR CONDITIONS OF ANY KIND, either express or i\
mplied.\nSee the License for the specific language\
 governing permissions and\nlimitations under the \
License.\n\n=head1 VERSION\n\n$Id: ncbiblast_lwp.p\
l 2560 2013-03-20 12:56:31Z hpm $\n\n=cut\n\nuse s\
trict;\nuse warnings;\n\nuse English;\nuse LWP;\nu\
se XML::Simple;\nuse Getopt::Long qw(:config no_ig\
nore_case bundling);\nuse File::Basename;\nuse Dat\
a::Dumper;\n\nmy $baseUrl = 'http://www.ebi.ac.uk/\
Tools/services/rest/ncbiblast';\n\nmy $checkInterv\
al = 3;\n\nmy $outputLevel = 1;\n\nmy $numOpts = s\
calar(@ARGV);\nmy %params = ( 'debugLevel' => 0 );\
\n\nmy %tool_params = ();\nGetOptions(\n\n	# Tool \
specific options\n	'program|p=s'  => \\$tool_param\
s{'program'},   # blastp, blastn, blastx, etc.\n	'\
database|D=s' => \\$params{'database'},       # Da\
tabase(s) to search\n	'matrix|m=s'   => \\$tool_pa\
rams{'matrix'},    # Scoring martix to use\n	'exp|\
E=f'      => \\$tool_params{'exp'},       # E-valu\
e threshold\n	'filter|f=s'   => \\$tool_params{'fi\
lter'},    # Low complexity filter\n	'align|A=i'  \
  => \\$tool_params{'align'},     # Pairwise align\
ment format\n	'scores|s=i'   => \\$tool_params{'sc\
ores'},    # Number of scores\n	'alignments|n=i' =\
> \\$tool_params{'alignments'},   # Number of alig\
nments\n	'dropoff|d=i'    => \\$tool_params{'dropo\
ff'},      # Dropoff score\n	'match_scores=s' => \\
\$tool_params{'match_scores'}, # Match/missmatch s\
cores\n	'match|u=i'      => \\$params{'match'},   \
          # Match score\n	'mismatch|v=i'   => \\$p\
arams{'mismatch'},          # Mismatch score\n	'ga\
popen|o=i'    => \\$tool_params{'gapopen'},      #\
 Open gap penalty\n	'gapext|x=i'     => \\$tool_pa\
rams{'gapext'},       # Gap extension penality\n	'\
gapalign|g'     => \\$tool_params{'gapalign'},    \
 # Optimise gap alignments\n	'stype=s' => \\$tool_\
params{'stype'},    # Sequence type\n	'seqrange=s'\
 => \\$tool_params{'seqrange'},    # Query subsequ\
ence\n	'sequence=s' => \\$params{'sequence'},     \
    # Query sequence\n	'multifasta' => \\$params{'\
multifasta'},       # Multiple fasta input\n\n	# C\
ompatability options, old command-line\n	'numal|n=\
i'     => \\$params{'numal'},        # Number of a\
lignments\n	'opengap|o=i'   => \\$params{'opengap'\
},      # Open gap penalty\n	'extendgap|x=i' => \\\
$params{'extendgap'},    # Gap extension penality\\
n	\n	# Generic options\n	'email=s'       => \\$par\
ams{'email'},          # User e-mail address\n	'ti\
tle=s'       => \\$params{'title'},          # Job\
 title\n	'outfile=s'     => \\$params{'outfile'}, \
       # Output file name\n	'outformat=s'   => \\$\
params{'outformat'},      # Output file type\n	'jo\
bid=s'       => \\$params{'jobid'},          # Job\
Id\n	'help|h'        => \\$params{'help'},        \
   # Usage help\n	'async'         => \\$params{'as\
ync'},          # Asynchronous submission\n	'pollj\
ob'       => \\$params{'polljob'},        # Get re\
sults\n	'resultTypes'   => \\$params{'resultTypes'\
},    # Get result types\n	'status'        => \\$p\
arams{'status'},         # Get status\n	'params'  \
      => \\$params{'params'},         # List input\
 parameters\n	'paramDetail=s' => \\$params{'paramD\
etail'},    # Get details for parameter\n	'quiet' \
        => \\$params{'quiet'},          # Decrease\
 output level\n	'verbose'       => \\$params{'verb\
ose'},        # Increase output level\n	'debugLeve\
l=i'  => \\$params{'debugLevel'},     # Debug outp\
ut level\n	'baseUrl=s'     => \\$baseUrl,         \
         # Base URL for service.\n);\nif ( $params\
{'verbose'} ) { $outputLevel++ }\nif ( $params{'qu\
iet'} )  { $outputLevel-- }\n\n&print_debug_messag\
e( 'MAIN', 'LWP::VERSION: ' . $LWP::VERSION,\n	1 )\
;\n\n&print_debug_message( 'MAIN', \"params:\\n\" \
. Dumper( \\%params ),           11 );\n&print_deb\
ug_message( 'MAIN', \"tool_params:\\n\" . Dumper( \
\\%tool_params ), 11 );\n\nmy $ua;\n\nmy $scriptNa\
me = basename( $0, () );\n\nif ( $params{'help'} |\
| $numOpts == 0 ) {\n	&usage();\n	exit(0);\n}\n\n&\
print_debug_message( 'MAIN', 'baseUrl: ' . $baseUr\
l, 1 );\n\nif (\n	!(\n		   $params{'polljob'}\n		|\
| $params{'resultTypes'}\n		|| $params{'status'}\n\
		|| $params{'params'}\n		|| $params{'paramDetail'\
}\n	)\n	&& !( defined( $ARGV[0] ) || defined( $par\
ams{'sequence'} ) )\n  )\n{\n\n	# Bad argument com\
bination, so print error message and usage\n	print\
 STDERR 'Error: bad option combination', \"\\n\";\\
n	&usage();\n	exit(1);\n}\n\nelsif ( $params{'para\
ms'} ) {\n	&print_tool_params();\n}\n\nelsif ( $pa\
rams{'paramDetail'} ) {\n	&print_param_details( $p\
arams{'paramDetail'} );\n}\n\nelsif ( $params{'sta\
tus'} && defined( $params{'jobid'} ) ) {\n	&print_\
job_status( $params{'jobid'} );\n}\n\nelsif ( $par\
ams{'resultTypes'} && defined( $params{'jobid'} ) \
) {\n	&print_result_types( $params{'jobid'} );\n}\\
n\nelsif ( $params{'polljob'} && defined( $params{\
'jobid'} ) ) {\n	&get_results( $params{'jobid'} );\
\n}\n\nelse {\n\n	# Multiple input sequence mode, \
assume fasta format.\n	if ( $params{'multifasta'} \
) {\n		&multi_submit_job();\n	}\n\n	# Entry identi\
fier list file.\n	elsif (( defined( $params{'seque\
nce'} ) && $params{'sequence'} =~ m/^\\@/ )\n		|| \
( defined( $ARGV[0] ) && $ARGV[0] =~ m/^\\@/ ) )\n\
	{\n		my $list_filename = $params{'sequence'} || $\
ARGV[0];\n		$list_filename =~ s/^\\@//;\n		&list_f\
ile_submit_job($list_filename);\n	}\n\n	# Default:\
 single sequence/identifier.\n	else {\n\n		# Load \
the sequence data and submit.\n		&submit_job( &loa\
d_data() );\n	}\n}\n\n=head1 FUNCTIONS\n\n=cut\n\n\
\n=head2 rest_user_agent()\n\nGet a LWP UserAgent \
to use to perform REST requests.\n\n  my $ua = &re\
st_user_agent();\n\n=cut\n\nsub rest_user_agent() \
{\n	print_debug_message( 'rest_user_agent', 'Begin\
', 21 );\n	# Create an LWP UserAgent for making HT\
TP calls.\n	my $ua = LWP::UserAgent->new();\n	# Se\
t 'User-Agent' HTTP header to identifiy the client\
.\n	'$Revision: 2560 $' =~ m/(\\d+)/;\n	$ua->agent\
(\"EBI-Sample-Client/$1 ($scriptName; $OSNAME) \" \
. $ua->agent());\n	# Configure HTTP proxy support \
from environment.\n	$ua->env_proxy;\n	print_debug_\
message( 'rest_user_agent', 'End', 21 );\n	return \
$ua;\n}\n\n=head2 rest_error()\n\nCheck a REST res\
ponse for an error condition. An error is mapped t\
o a die.\n\n  &rest_error($response, $content_data\
);\n\n=cut\n\nsub rest_error() {\n	print_debug_mes\
sage( 'rest_error', 'Begin', 21 );\n	my $response \
= shift;\n	my $contentdata;\n	if(scalar(@_) > 0) {\
\n		$contentdata = shift;\n	}\n	if(!defined($conte\
ntdata) || $contentdata eq '') {\n		$contentdata =\
 $response->content();\n	}\n	# Check for HTTP erro\
r codes\n	if ( $response->is_error ) {\n		my $erro\
r_message = '';\n		# HTML response.\n		if(	$conten\
tdata =~ m/<h1>([^<]+)<\\/h1>/ ) {\n			$error_mess\
age = $1;\n		}\n		#  XML response.\n		elsif($conte\
ntdata =~ m/<description>([^<]+)<\\/description>/)\
 {\n			$error_message = $1;\n		}\n		die 'http stat\
us: ' . $response->code . ' ' . $response->message\
 . '  ' . $error_message;\n	}\n	print_debug_messag\
e( 'rest_error', 'End', 21 );\n}\n\n=head2 rest_re\
quest()\n\nPerform a REST request (HTTP GET).\n\n \
 my $response_str = &rest_request($url);\n\n=cut\n\
\nsub rest_request {\n	print_debug_message( 'rest_\
request', 'Begin', 11 );\n	my $requestUrl = shift;\
\n	print_debug_message( 'rest_request', 'URL: ' . \
$requestUrl, 11 );\n\n	# Get an LWP UserAgent.\n	$\
ua = &rest_user_agent() unless defined($ua);\n	# A\
vailable HTTP compression methods.\n	my $can_accep\
t;\n	eval {\n	    $can_accept = HTTP::Message::dec\
odable();\n	};\n	$can_accept = '' unless defined($\
can_accept);\n	# Perform the request\n	my $respons\
e = $ua->get($requestUrl,\n		'Accept-Encoding' => \
$can_accept, # HTTP compression.\n	);\n	print_debu\
g_message( 'rest_request', 'HTTP status: ' . $resp\
onse->code,\n		11 );\n	print_debug_message( 'rest_\
request',\n		'response length: ' . length($respons\
e->content()), 11 );\n	print_debug_message( 'rest_\
request',\n		'request:' .\"\\n\" . $response->requ\
est()->as_string(), 32 );\n	print_debug_message( '\
rest_request',\n		'response: ' . \"\\n\" . $respon\
se->as_string(), 32 );\n	# Unpack possibly compres\
sed response.\n	my $retVal;\n	if ( defined($can_ac\
cept) && $can_accept ne '') {\n	    $retVal = $res\
ponse->decoded_content();\n	}\n	# If unable to dec\
ode use orginal content.\n	$retVal = $response->co\
ntent() unless defined($retVal);\n	# Check for an \
error.\n	&rest_error($response, $retVal);\n	print_\
debug_message( 'rest_request', 'retVal: ' . $retVa\
l, 12 );\n	print_debug_message( 'rest_request', 'E\
nd', 11 );\n\n	# Return the response data\n	return\
 $retVal;\n}\n\n=head2 rest_get_parameters()\n\nGe\
t list of tool parameter names.\n\n  my (@param_li\
st) = &rest_get_parameters();\n\n=cut\n\nsub rest_\
get_parameters {\n	print_debug_message( 'rest_get_\
parameters', 'Begin', 1 );\n	my $url              \
  = $baseUrl . '/parameters/';\n	my $param_list_xm\
l_str = rest_request($url);\n	my $param_list_xml  \
   = XMLin($param_list_xml_str);\n	my (@param_list\
)       = @{ $param_list_xml->{'id'} };\n	print_de\
bug_message( 'rest_get_parameters', 'End', 1 );\n	\
return (@param_list);\n}\n\n=head2 rest_get_parame\
ter_details()\n\nGet details of a tool parameter.\\
n\n  my $paramDetail = &rest_get_parameter_details\
($param_name);\n\n=cut\n\nsub rest_get_parameter_d\
etails {\n	print_debug_message( 'rest_get_paramete\
r_details', 'Begin', 1 );\n	my $parameterId = shif\
t;\n	print_debug_message( 'rest_get_parameter_deta\
ils',\n		'parameterId: ' . $parameterId, 1 );\n	my\
 $url                  = $baseUrl . '/parameterdet\
ails/' . $parameterId;\n	my $param_detail_xml_str \
= rest_request($url);\n	my $param_detail_xml     =\
 XMLin($param_detail_xml_str);\n	print_debug_messa\
ge( 'rest_get_parameter_details', 'End', 1 );\n	re\
turn ($param_detail_xml);\n}\n\n=head2 rest_run()\\
n\nSubmit a job.\n\n  my $job_id = &rest_run($emai\
l, $title, \\%params );\n\n=cut\n\nsub rest_run {\\
n	print_debug_message( 'rest_run', 'Begin', 1 );\n\
	my $email  = shift;\n	my $title  = shift;\n	my $p\
arams = shift;\n	print_debug_message( 'rest_run', \
'email: ' . $email, 1 );\n	if ( defined($title) ) \
{\n		print_debug_message( 'rest_run', 'title: ' . \
$title, 1 );\n	}\n	print_debug_message( 'rest_run'\
, 'params: ' . Dumper($params), 1 );\n\n	# Get an \
LWP UserAgent.\n	$ua = &rest_user_agent() unless d\
efined($ua);\n\n	# Clean up parameters\n	my (%tmp_\
params) = %{$params};\n	$tmp_params{'email'} = $em\
ail;\n	$tmp_params{'title'} = $title;\n	foreach my\
 $param_name ( keys(%tmp_params) ) {\n		if ( !defi\
ned( $tmp_params{$param_name} ) ) {\n			delete $tm\
p_params{$param_name};\n		}\n	}\n\n	# Submit the j\
ob as a POST\n	my $url = $baseUrl . '/run';\n	my $\
response = $ua->post( $url, \\%tmp_params );\n	pri\
nt_debug_message( 'rest_run', 'HTTP status: ' . $r\
esponse->code, 11 );\n	print_debug_message( 'rest_\
run',\n		'request:' .\"\\n\" . $response->request(\
)->as_string(), 11 );\n	print_debug_message( 'rest\
_run',\n		'response: ' . length($response->as_stri\
ng()) . \"\\n\" . $response->as_string(), 11 );\n\\
n	# Check for an error.\n	&rest_error($response);\\
n\n	# The job id is returned\n	my $job_id = $respo\
nse->content();\n	print_debug_message( 'rest_run',\
 'End', 1 );\n	return $job_id;\n}\n\n=head2 rest_g\
et_status()\n\nCheck the status of a job.\n\n  my \
$status = &rest_get_status($job_id);\n\n=cut\n\nsu\
b rest_get_status {\n	print_debug_message( 'rest_g\
et_status', 'Begin', 1 );\n	my $job_id = shift;\n	\
print_debug_message( 'rest_get_status', 'jobid: ' \
. $job_id, 2 );\n	my $status_str = 'UNKNOWN';\n	my\
 $url        = $baseUrl . '/status/' . $job_id;\n	\
$status_str = &rest_request($url);\n	print_debug_m\
essage( 'rest_get_status', 'status_str: ' . $statu\
s_str, 2 );\n	print_debug_message( 'rest_get_statu\
s', 'End', 1 );\n	return $status_str;\n}\n\n=head2\
 rest_get_result_types()\n\nGet list of result typ\
es for finished job.\n\n  my (@result_types) = &re\
st_get_result_types($job_id);\n\n=cut\n\nsub rest_\
get_result_types {\n	print_debug_message( 'rest_ge\
t_result_types', 'Begin', 1 );\n	my $job_id = shif\
t;\n	print_debug_message( 'rest_get_result_types',\
 'jobid: ' . $job_id, 2 );\n	my (@resultTypes);\n	\
my $url                      = $baseUrl . '/result\
types/' . $job_id;\n	my $result_type_list_xml_str \
= &rest_request($url);\n	my $result_type_list_xml \
    = XMLin($result_type_list_xml_str);\n	(@result\
Types) = @{ $result_type_list_xml->{'type'} };\n	p\
rint_debug_message( 'rest_get_result_types',\n		sc\
alar(@resultTypes) . ' result types', 2 );\n	print\
_debug_message( 'rest_get_result_types', 'End', 1 \
);\n	return (@resultTypes);\n}\n\n=head2 rest_get_\
result()\n\nGet result data of a specified type fo\
r a finished job.\n\n  my $result = rest_get_resul\
t($job_id, $result_type);\n\n=cut\n\nsub rest_get_\
result {\n	print_debug_message( 'rest_get_result',\
 'Begin', 1 );\n	my $job_id = shift;\n	my $type   \
= shift;\n	print_debug_message( 'rest_get_result',\
 'jobid: ' . $job_id, 1 );\n	print_debug_message( \
'rest_get_result', 'type: ' . $type,    1 );\n	my \
$url    = $baseUrl . '/result/' . $job_id . '/' . \
$type;\n	my $result = &rest_request($url);\n	print\
_debug_message( 'rest_get_result', length($result)\
 . ' characters',\n		1 );\n	print_debug_message( '\
rest_get_result', 'End', 1 );\n	return $result;\n}\
\n\n\n=head2 print_debug_message()\n\nPrint debug \
message at specified debug level.\n\n  &print_debu\
g_message($method_name, $message, $level);\n\n=cut\
\n\nsub print_debug_message {\n	my $function_name \
= shift;\n	my $message       = shift;\n	my $level \
        = shift;\n	if ( $level <= $params{'debugLe\
vel'} ) {\n		print STDERR '[', $function_name, '()\
] ', $message, \"\\n\";\n	}\n}\n\n=head2 print_too\
l_params()\n\nPrint list of tool parameters.\n\n  \
&print_tool_params();\n\n=cut\n\nsub print_tool_pa\
rams {\n	print_debug_message( 'print_tool_params',\
 'Begin', 1 );\n	my (@param_list) = &rest_get_para\
meters();\n	foreach my $param ( sort(@param_list) \
) {\n		print $param, \"\\n\";\n	}\n	print_debug_me\
ssage( 'print_tool_params', 'End', 1 );\n}\n\n=hea\
d2 print_param_details()\n\nPrint details of a too\
l parameter.\n\n  &print_param_details($param_name\
);\n\n=cut\n\nsub print_param_details {\n	print_de\
bug_message( 'print_param_details', 'Begin', 1 );\\
n	my $paramName = shift;\n	print_debug_message( 'p\
rint_param_details', 'paramName: ' . $paramName, 2\
 );\n	my $paramDetail = &rest_get_parameter_detail\
s($paramName);\n	print $paramDetail->{'name'}, \"\\
\t\", $paramDetail->{'type'}, \"\\n\";\n	print $pa\
ramDetail->{'description'}, \"\\n\";\n	if(defined(\
$paramDetail->{'values'}->{'value'})) {\n		if(ref(\
$paramDetail->{'values'}->{'value'}) eq 'ARRAY') {\
\n			foreach my $value ( @{ $paramDetail->{'values\
'}->{'value'} } ) {\n				&print_param_value($value\
);\n			}\n		}\n		else {\n				&print_param_value($p\
aramDetail->{'values'}->{'value'});\n		}\n	}\n	pri\
nt_debug_message( 'print_param_details', 'End', 1 \
);\n}\n\n=head2 print_param_value()\n\nPrint detai\
ls of a tool parameter value.\n\n  &print_param_de\
tails($param_value);\n\nUsed by print_param_detail\
s() to handle both singluar and array values.\n\n=\
cut\n\nsub print_param_value {\n	my $value = shift\
;\n	print $value->{'value'};\n	if ( $value->{'defa\
ultValue'} eq 'true' ) {\n		print \"\\t\", 'defaul\
t';\n	}\n	print \"\\n\";\n	print \"\\t\", $value->\
{'label'}, \"\\n\";\n	if ( defined( $value->{'prop\
erties'} ) ) {\n		foreach\n		  my $key ( sort( key\
s( %{ $value->{'properties'}{'property'} } ) ) )\n\
		{\n			if ( ref( $value->{'properties'}{'property\
'}{$key} ) eq 'HASH'\n				&& defined( $value->{'pr\
operties'}{'property'}{$key}{'value'} )\n			  )\n	\
		{\n				print \"\\t\", $key, \"\\t\",\n				  $val\
ue->{'properties'}{'property'}{$key}{'value'}, \"\\
\n\";\n			}\n			else {\n				print \"\\t\", $value-\
>{'properties'}{'property'}{'key'},\n				  \"\\t\"\
, $value->{'properties'}{'property'}{'value'}, \"\\
\n\";\n				last;\n			}\n		}\n	}\n}\n\n=head2 print\
_job_status()\n\nPrint status of a job.\n\n  &prin\
t_job_status($job_id);\n\n=cut\n\nsub print_job_st\
atus {\n	print_debug_message( 'print_job_status', \
'Begin', 1 );\n	my $jobid = shift;\n	print_debug_m\
essage( 'print_job_status', 'jobid: ' . $jobid, 1 \
);\n	if ( $outputLevel > 0 ) {\n		print STDERR 'Ge\
tting status for job ', $jobid, \"\\n\";\n	}\n	my \
$result = &rest_get_status($jobid);\n	print \"$res\
ult\\n\";\n	if ( $result eq 'FINISHED' && $outputL\
evel > 0 ) {\n		print STDERR \"To get results: $sc\
riptName --polljob --jobid \" . $jobid\n		  . \"\\\
n\";\n	}\n	print_debug_message( 'print_job_status'\
, 'End', 1 );\n}\n\n=head2 print_result_types()\n\\
nPrint available result types for a job.\n\n  &pri\
nt_result_types($job_id);\n\n=cut\n\nsub print_res\
ult_types {\n	print_debug_message( 'result_types',\
 'Begin', 1 );\n	my $jobid = shift;\n	print_debug_\
message( 'result_types', 'jobid: ' . $jobid, 1 );\\
n	if ( $outputLevel > 0 ) {\n		print STDERR 'Getti\
ng result types for job ', $jobid, \"\\n\";\n	}\n	\
my $status = &rest_get_status($jobid);\n	if ( $sta\
tus eq 'PENDING' || $status eq 'RUNNING' ) {\n		pr\
int STDERR 'Error: Job status is ', $status,\n		  \
'. To get result types the job must be finished.',\
 \"\\n\";\n	}\n	else {\n		my (@resultTypes) = &res\
t_get_result_types($jobid);\n		if ( $outputLevel >\
 0 ) {\n			print STDOUT 'Available result types:',\
 \"\\n\";\n		}\n		foreach my $resultType (@resultT\
ypes) {\n			print STDOUT $resultType->{'identifier\
'}, \"\\n\";\n			if ( defined( $resultType->{'labe\
l'} ) ) {\n				print STDOUT \"\\t\", $resultType->\
{'label'}, \"\\n\";\n			}\n			if ( defined( $resul\
tType->{'description'} ) ) {\n				print STDOUT \"\\
\t\", $resultType->{'description'}, \"\\n\";\n			}\
\n			if ( defined( $resultType->{'mediaType'} ) ) \
{\n				print STDOUT \"\\t\", $resultType->{'mediaT\
ype'}, \"\\n\";\n			}\n			if ( defined( $resultTyp\
e->{'fileSuffix'} ) ) {\n				print STDOUT \"\\t\",\
 $resultType->{'fileSuffix'}, \"\\n\";\n			}\n		}\\
n		if ( $status eq 'FINISHED' && $outputLevel > 0 \
) {\n			print STDERR \"\\n\", 'To get results:', \\
"\\n\",\n			  \"  $scriptName --polljob --jobid \"\
 . $params{'jobid'} . \"\\n\",\n			  \"  $scriptNa\
me --polljob --outformat <type> --jobid \"\n			  .\
 $params{'jobid'} . \"\\n\";\n		}\n	}\n	print_debu\
g_message( 'result_types', 'End', 1 );\n}\n\n=head\
2 submit_job()\n\nSubmit a job to the service.\n\n\
  &submit_job($seq);\n\n=cut\n\nsub submit_job {\n\
	print_debug_message( 'submit_job', 'Begin', 1 );\\
n\n	# Set input sequence\n	$tool_params{'sequence'\
} = shift;\n\n	# Load parameters\n	&load_params();\
\n\n	# Submit the job\n	my $jobid = &rest_run( $pa\
rams{'email'}, $params{'title'}, \\%tool_params );\
\n\n	# Simulate sync/async mode\n	if ( defined( $p\
arams{'async'} ) ) {\n		print STDOUT $jobid, \"\\n\
\";\n		if ( $outputLevel > 0 ) {\n			print STDERR\\
n			  \"To check status: $scriptName --status --jo\
bid $jobid\\n\";\n		}\n	}\n	else {\n		if ( $output\
Level > 0 ) {\n			print STDERR \"JobId: $jobid\\n\\
";\n		}\n		sleep 1;\n		&get_results($jobid);\n	}\n\
	print_debug_message( 'submit_job', 'End', 1 );\n}\
\n\n=head2 multi_submit_job()\n\nSubmit multiple j\
obs assuming input is a collection of fasta format\
ted sequences.\n\n  &multi_submit_job();\n\n=cut\n\
\nsub multi_submit_job {\n	print_debug_message( 'm\
ulti_submit_job', 'Begin', 1 );\n	my $jobIdForFile\
name = 1;\n	$jobIdForFilename = 0 if ( defined( $p\
arams{'outfile'} ) );\n	my (@filename_list) = ();\\
n\n	# Query sequence\n	if ( defined( $ARGV[0] ) ) \
{    # Bare option\n		if ( -f $ARGV[0] || $ARGV[0]\
 eq '-' ) {    # File\n			push( @filename_list, $A\
RGV[0] );\n		}\n		else {\n			warn 'Warning: Input \
file \"' . $ARGV[0] . '\" does not exist'\n		}\n	}\
\n	if ( $params{'sequence'} ) {                   \
# Via --sequence\n		if ( -f $params{'sequence'} ||\
 $params{'sequence'} eq '-' ) {    # File\n			push\
( @filename_list, $params{'sequence'} );\n		}\n		e\
lse {\n			warn 'Warning: Input file \"' . $params{\
'sequence'} . '\" does not exist'\n		}\n	}\n\n	$/ \
= '>';\n	foreach my $filename (@filename_list) {\n\
		my $INFILE;\n		if($filename eq '-') { # STDIN.\n\
			open( $INFILE, '<-' )\n			  or die 'Error: unab\
le to STDIN (' . $! . ')';\n		} else { # File.\n		\
	open( $INFILE, '<', $filename )\n			  or die 'Err\
or: unable to open file ' . $filename . ' (' . $! \
. ')';\n		}\n		while (<$INFILE>) {\n			my $seq = $\
_;\n			$seq =~ s/>$//;\n			if ( $seq =~ m/(\\S+)/ \
) {\n				print STDERR \"Submitting job for: $1\\n\\
"\n				  if ( $outputLevel > 0 );\n				$seq = '>' \
. $seq;\n				&print_debug_message( 'multi_submit_j\
ob', $seq, 11 );\n				&submit_job($seq);\n				$par\
ams{'outfile'} = undef if ( $jobIdForFilename == 1\
 );\n			}\n		}\n		close $INFILE;\n	}\n	print_debug\
_message( 'multi_submit_job', 'End', 1 );\n}\n\n=h\
ead2 list_file_submit_job()\n\nSubmit multiple job\
s using a file containing a list of entry identifi\
ers as \ninput.\n\n  &list_file_submit_job($list_f\
ilename)\n\n=cut\n\nsub list_file_submit_job {\n	m\
y $filename         = shift;\n	my $jobIdForFilenam\
e = 1;\n	$jobIdForFilename = 0 if ( defined( $para\
ms{'outfile'} ) );\n\n	# Iterate over identifiers,\
 submitting each job\n	my $LISTFILE;\n	if($filenam\
e eq '-') { # STDIN.\n		open( $LISTFILE, '<-' )\n	\
	  or die 'Error: unable to STDIN (' . $! . ')';\n\
	} else { # File.\n		open( $LISTFILE, '<', $filena\
me )\n		  or die 'Error: unable to open file ' . $\
filename . ' (' . $! . ')';\n	}\n	while (<$LISTFIL\
E>) {\n		my $line = $_;\n		chomp($line);\n		if ( $\
line ne '' ) {\n			&print_debug_message( 'list_fil\
e_submit_job', 'line: ' . $line, 2 );\n			if ( $li\
ne =~ m/\\w:\\w/ ) {    # Check this is an identif\
ier\n				print STDERR \"Submitting job for: $line\\
\n\"\n				  if ( $outputLevel > 0 );\n				&submit_\
job($line);\n			}\n			else {\n				print STDERR\n\"\
Warning: line \\\"$line\\\" is not recognised as a\
n identifier\\n\";\n			}\n		}\n		$params{'outfile'\
} = undef if ( $jobIdForFilename == 1 );\n	}\n	clo\
se $LISTFILE;\n}\n\n=head2 load_data()\n\nLoad seq\
uence data from file or option specified on the co\
mmand-line.\n\n  &load_data();\n\n=cut\n\nsub load\
_data {\n	print_debug_message( 'load_data', 'Begin\
', 1 );\n	my $retSeq;\n\n	# Query sequence\n	if ( \
defined( $ARGV[0] ) ) {    # Bare option\n		if ( -\
f $ARGV[0] || $ARGV[0] eq '-' ) {    # File\n			$r\
etSeq = &read_file( $ARGV[0] );\n		}\n		else {    \
                                 # DB:ID or sequen\
ce\n			$retSeq = $ARGV[0];\n		}\n	}\n	if ( $params\
{'sequence'} ) {                   # Via --sequenc\
e\n		if ( -f $params{'sequence'} || $params{'seque\
nce'} eq '-' ) {    # File\n			$retSeq = &read_fil\
e( $params{'sequence'} );\n		}\n		else {    # DB:I\
D or sequence\n			$retSeq = $params{'sequence'};\n\
		}\n	}\n	print_debug_message( 'load_data', 'End',\
 1 );\n	return $retSeq;\n}\n\n=head2 load_params()\
\n\nLoad job parameters from command-line options.\
\n\n  &load_params();\n\n=cut\n\nsub load_params {\
\n	print_debug_message( 'load_params', 'Begin', 1 \
);\n\n	# Database(s) to search\n	my (@dbList) = sp\
lit /[ ,]/, $params{'database'};\n	$tool_params{'d\
atabase'} = \\@dbList;\n\n	# Match/missmatch\n	if \
( $params{'match'} && $params{'missmatch'} ) {\n		\
$tool_params{'match_scores'} =\n		  $params{'match\
'} . ',' . $params{'missmatch'};\n	}\n	\n	# Compat\
ability options, old command-line\n	if(!$tool_para\
ms{'alignments'} && $params{'numal'}) {\n		$tool_p\
arams{'alignments'} = $params{'numal'};\n	}\n	if(!\
$tool_params{'gapopen'} && $params{'opengap'}) {\n\
		$tool_params{'gapopen'} = $params{'opengap'};\n	\
}\n	if(!$tool_params{'gapext'} && $params{'extendg\
ap'}) {\n		$tool_params{'gapext'} = $params{'exten\
dgap'};\n	}\n\n	print_debug_message( 'load_params'\
, 'End', 1 );\n}\n\n=head2 client_poll()\n\nClient\
-side job polling.\n\n  &client_poll($job_id);\n\n\
=cut\n\nsub client_poll {\n	print_debug_message( '\
client_poll', 'Begin', 1 );\n	my $jobid  = shift;\\
n	my $status = 'PENDING';\n\n	my $errorCount = 0;\\
n	while ($status eq 'RUNNING'\n		|| $status eq 'PE\
NDING'\n		|| ( $status eq 'ERROR' && $errorCount <\
 2 ) )\n	{\n		$status = rest_get_status($jobid);\n\
		print STDERR \"$status\\n\" if ( $outputLevel > \
0 );\n		if ( $status eq 'ERROR' ) {\n			$errorCoun\
t++;\n		}\n		elsif ( $errorCount > 0 ) {\n			$erro\
rCount--;\n		}\n		if (   $status eq 'RUNNING'\n			\
|| $status eq 'PENDING'\n			|| $status eq 'ERROR' \
)\n		{\n\n			# Wait before polling again.\n			slee\
p $checkInterval;\n		}\n	}\n	print_debug_message( \
'client_poll', 'End', 1 );\n	return $status;\n}\n\\
n=head2 get_results()\n\nGet the results for a job\
 identifier.\n\n  &get_results($job_id);\n\n=cut\n\
\nsub get_results {\n	print_debug_message( 'get_re\
sults', 'Begin', 1 );\n	my $jobid = shift;\n	print\
_debug_message( 'get_results', 'jobid: ' . $jobid,\
 1 );\n\n	# Verbose\n	if ( $outputLevel > 1 ) {\n	\
	print 'Getting results for job ', $jobid, \"\\n\"\
;\n	}\n\n	# Check status, and wait if not finished\
\n	client_poll($jobid);\n\n	# Use JobId if output \
file name is not defined\n	unless ( defined( $para\
ms{'outfile'} ) ) {\n		$params{'outfile'} = $jobid\
;\n	}\n\n	# Get list of data types\n	my (@resultTy\
pes) = rest_get_result_types($jobid);\n\n	# Get th\
e data and write it to a file\n	if ( defined( $par\
ams{'outformat'} ) ) {    # Specified data type\n	\
	my $selResultType;\n		foreach my $resultType (@re\
sultTypes) {\n			if ( $resultType->{'identifier'} \
eq $params{'outformat'} ) {\n				$selResultType = \
$resultType;\n			}\n		}\n		if ( defined($selResult\
Type) ) {\n			my $result =\n			  rest_get_result( \
$jobid, $selResultType->{'identifier'} );\n			if (\
 $params{'outfile'} eq '-' ) {\n				write_file( $p\
arams{'outfile'}, $result );\n			}\n			else {\n			\
	write_file(\n					$params{'outfile'} . '.'\n					\
  . $selResultType->{'identifier'} . '.'\n					  .\
 $selResultType->{'fileSuffix'},\n					$result\n		\
		);\n			}\n		}\n		else {\n			die 'Error: unknown \
result format \"' . $params{'outformat'} . '\"';\n\
		}\n	}\n	else {    # Data types available\n		    \
  # Write a file for each output type\n		for my $r\
esultType (@resultTypes) {\n			if ( $outputLevel >\
 1 ) {\n				print STDERR 'Getting ', $resultType->\
{'identifier'}, \"\\n\";\n			}\n			my $result = re\
st_get_result( $jobid, $resultType->{'identifier'}\
 );\n			if ( $params{'outfile'} eq '-' ) {\n				wr\
ite_file( $params{'outfile'}, $result );\n			}\n		\
	else {\n				write_file(\n					$params{'outfile'} \
. '.'\n					  . $resultType->{'identifier'} . '.'\\
n					  . $resultType->{'fileSuffix'},\n					$resu\
lt\n				);\n			}\n		}\n	}\n	print_debug_message( '\
get_results', 'End', 1 );\n}\n\n=head2 read_file()\
\n\nRead a file into a scalar. The special filenam\
e '-' can be used to read from \nstandard input (S\
TDIN).\n\n  my $data = &read_file($filename);\n\n=\
cut\n\nsub read_file {\n	print_debug_message( 'rea\
d_file', 'Begin', 1 );\n	my $filename = shift;\n	p\
rint_debug_message( 'read_file', 'filename: ' . $f\
ilename, 2 );\n	my ( $content, $buffer );\n	if ( $\
filename eq '-' ) {\n		while ( sysread( STDIN, $bu\
ffer, 1024 ) ) {\n			$content .= $buffer;\n		}\n	}\
\n	else {    # File\n		open( my $FILE, '<', $filen\
ame )\n		  or die \"Error: unable to open input fi\
le $filename ($!)\";\n		while ( sysread( $FILE, $b\
uffer, 1024 ) ) {\n			$content .= $buffer;\n		}\n	\
	close($FILE);\n	}\n	print_debug_message( 'read_fi\
le', 'End', 1 );\n	return $content;\n}\n\n=head2 w\
rite_file()\n\nWrite data to a file. The special f\
ilename '-' can be used to write to \nstandard out\
put (STDOUT).\n\n  &write_file($filename, $data);\\
n\n=cut\n\nsub write_file {\n	print_debug_message(\
 'write_file', 'Begin', 1 );\n	my ( $filename, $da\
ta ) = @_;\n	print_debug_message( 'write_file', 'f\
ilename: ' . $filename, 2 );\n	if ( $outputLevel >\
 0 ) {\n		print STDERR 'Creating result file: ' . \
$filename . \"\\n\";\n	}\n	if ( $filename eq '-' )\
 {\n		print STDOUT $data;\n	}\n	else {\n		open( my\
 $FILE, '>', $filename )\n		  or die \"Error: unab\
le to open output file $filename ($!)\";\n		syswri\
te( $FILE, $data );\n		close($FILE);\n	}\n	print_d\
ebug_message( 'write_file', 'End', 1 );\n}\n\n=hea\
d2 usage()\n\nPrint program usage message.\n\n  &u\
sage();\n\n=cut\n\nsub usage {\n	print STDERR <<EO\
F\nNCBI BLAST\n==========\n   \nRapid sequence dat\
abase search programs utilizing the BLAST algorith\
m\n    \n[Required]\n\n  -p, --program      : str \
 : BLAST program to use, see --paramDetail program\
\n  -D, --database     : str  : database(s) to sea\
rch, space separated. See\n                       \
       --paramDetail database\n      --stype      \
  : str  : query sequence type, see --paramDetail \
stype\n  seqFile            : file : query sequenc\
e (\"-\" for STDIN, \\@filename for\n             \
                 identifier list file)\n\n[Optiona\
l]\n\n  -m, --matrix       : str  : scoring matrix\
, see --paramDetail matrix\n  -e, --exp          :\
 real : 0<E<= 1000. Statistical significance thres\
hold \n                              for reporting\
 database sequence matches.\n  -f, --filter       \
:      : filter the query sequence for low complex\
ity \n                              regions, see -\
-paramDetail filter\n  -A, --align        : int  :\
 pairwise alignment format, see --paramDetail alig\
n\n  -s, --scores       : int  : number of scores \
to be reported\n  -n, --alignments   : int  : numb\
er of alignments to report\n  -u, --match        :\
 int  : Match score (BLASTN only)\n  -v, --mismatc\
h     : int  : Mismatch score (BLASTN only)\n  -o,\
 --gapopen      : int  : Gap open penalty\n  -x, -\
-gapext       : int  : Gap extension penalty\n  -d\
, --dropoff      : int  : Drop-off\n  -g, --gapali\
gn     :      : Optimise gapped alignments\n      \
--seqrange     : str  : region within input to use\
 as query\n      --multifasta   :      : treat inp\
ut as a set of fasta formatted sequences\n\n[Gener\
al]\n\n  -h, --help         :      : prints this h\
elp text\n      --async        :      : forces to \
make an asynchronous query\n      --email        :\
 str  : e-mail address\n      --title        : str\
  : title for job\n      --status       :      : g\
et job status\n      --resultTypes  :      : get a\
vailable result types for job\n      --polljob    \
  :      : poll for the status of a job\n      --j\
obid        : str  : jobid that was returned when \
an asynchronous job \n                            \
  was submitted.\n      --outfile      : str  : fi\
le name for results (default is jobid;\n          \
                    \"-\" for STDOUT)\n      --out\
format    : str  : result format to retrieve\n    \
  --params       :      : list input parameters\n \
     --paramDetail  : str  : display details for i\
nput parameter\n      --quiet        :      : decr\
ease output\n      --verbose      :      : increas\
e output\n   \nSynchronous job:\n\n  The results/e\
rrors are returned as soon as the job is finished.\
\n  Usage: $scriptName --email <your\\@email> [opt\
ions...] seqFile\n  Returns: results as an attachm\
ent\n\nAsynchronous job:\n\n  Use this if you want\
 to retrieve the results at a later time. The resu\
lts \n  are stored for up to 24 hours. 	\n  Usage:\
 $scriptName --async --email <your\\@email> [optio\
ns...] seqFile\n  Returns: jobid\n\n  Use the jobi\
d to query for the status of the job. If the job i\
s finished, \n  it also returns the results/errors\
.\n  Usage: $scriptName --polljob --jobid <jobId> \
[--outfile string]\n  Returns: string indicating t\
he status of the job and if applicable, results \n\
  as an attachment.\n\nFurther information:\n\n  h\
ttp://www.ebi.ac.uk/Tools/webservices/services/sss\
/ncbi_blast_rest\n  http://www.ebi.ac.uk/Tools/web\
services/tutorials/perl\n\nSupport/Feedback:\n\n  \
http://www.ebi.ac.uk/support/\nEOF\n}\n\n=head1 FE\
EDBACK/SUPPORT\n\nPlease contact us at L<http://ww\
w.ebi.ac.uk/support/> if you have any \nfeedback, \
suggestions or issues with the service or this cli\
ent.\n\n=cut\n","\n=head1 NAME\n\nwublast_lwp.pl\n\
\n=head1 DESCRIPTION\n\nWU-BLAST (REST) web servic\
e Perl client using L<LWP>.\n\nTested with:\n\n=ov\
er\n\n=item *\nL<LWP> 5.79, L<XML::Simple> 2.12 an\
d Perl 5.8.3\n\n=item *\nL<LWP> 5.808, L<XML::Simp\
le> 2.18 and Perl 5.8.8 (Ubuntu 8.04 LTS)\n\n=item\
 *\nL<LWP> 5.834, L<XML::Simple> 2.18 and Perl 5.1\
0.1 (Ubuntu 10.04 LTS)\n\n=item *\nL<LWP> 6.03, L<\
XML::Simple> 2.18 and Perl 5.14.2 (Ubuntu 12.04 LT\
S)\n\n=back\n\nFor further information see:\n\n=ov\
er\n\n=item *\nL<http://www.ebi.ac.uk/Tools/webser\
vices/services/sss/wu_blast_rest>\n\n=item *\nL<ht\
tp://www.ebi.ac.uk/Tools/webservices/tutorials/per\
l>\n\n=back\n\n=head1 LICENSE\n\nCopyright 2012-20\
13 EMBL - European Bioinformatics Institute\n\nLic\
ensed under the Apache License, Version 2.0 (the \\
"License\");\nyou may not use this file except in \
compliance with the License.\nYou may obtain a cop\
y of the License at\n\n    http://www.apache.org/l\
icenses/LICENSE-2.0\n\nUnless required by applicab\
le law or agreed to in writing, software\ndistribu\
ted under the License is distributed on an \"AS IS\
\" BASIS,\nWITHOUT WARRANTIES OR CONDITIONS OF ANY\
 KIND, either express or implied.\nSee the License\
 for the specific language governing permissions a\
nd\nlimitations under the License.\n\n=head1 VERSI\
ON\n\n$Id: wublast_lwp.pl 2560 2013-03-20 12:56:31\
Z hpm $\n\n=cut\n\nuse strict;\nuse warnings;\n\nu\
se English;\nuse LWP;\nuse XML::Simple;\nuse Getop\
t::Long qw(:config no_ignore_case bundling);\nuse \
File::Basename;\nuse Data::Dumper;\n\nmy $baseUrl \
= 'http://www.ebi.ac.uk/Tools/services/rest/wublas\
t';\n\nmy $checkInterval = 3;\n\nmy $outputLevel =\
 1;\n\nmy $numOpts = scalar(@ARGV);\nmy %params = \
( 'debugLevel' => 0 );\n\nmy %tool_params = ();\nG\
etOptions(\n\n	# Tool specific options\n	'program|\
p=s'     => \\$tool_params{'program'},      # BLAS\
T program\n	'database|D=s'    => \\$params{'databa\
se'},     # Search database\n	'matrix|m=s'      =>\
 \\$tool_params{'matrix'},       # Scoring matrix\\
n	'exp|E=f'         => \\$tool_params{'exp'},     \
     # E-value threshold\n	'viewfilter|e'    => \\\
$tool_params{'viewfilter'},   # Display filtered s\
equence\n	'filter|f=s'      => \\$tool_params{'fil\
ter'},       # Low complexity filter name\n	'align\
ments|n=i'  => \\$tool_params{'alignments'},   # N\
umber of alignments\n	'scores|s=i'      => \\$tool\
_params{'scores'},       # Number of scores\n	'sen\
sitivity|S=s' => \\$tool_params{'sensitivity'},  #\
 Search sensitivity\n	'sort|t=s'        => \\$tool\
_params{'sort'},         # Sort hits by...\n	'stat\
s|T=s'       => \\$tool_params{'stats'},        # \
Scoring statistic to use\n	'strand|d=s'      => \\\
$tool_params{'strand'},       # Strand to use\n	't\
opcombon|c=i'   => \\$tool_params{'topcombon'},   \
 # Consistent sets of HSPs\n	'align|A=i'       => \
\\$tool_params{'align'},   # Pairwise alignment fo\
rmat\n	'stype=s' => \\$tool_params{'stype'},    # \
Sequence type 'protein' or 'dna'\n	'sequence=s' =>\
 \\$params{'sequence'},         # Query sequence f\
ile or DB:ID\n	'multifasta' => \\$params{'multifas\
ta'},       # Multiple fasta input\n\n	# Compatabi\
lity options, old command-line.\n	'echofilter|e'  \
  => \\$params{'echofilter'},   # Display filtered\
 sequence\n	'b=i'  => \\$params{'numal'},        #\
 Number of alignments\n	'appxml=s'        => \\$pa\
rams{'appxml'},       # Application XML\n\n	# Gene\
ric options\n	'email=s'       => \\$params{'email'\
},          # User e-mail address\n	'title=s'     \
  => \\$params{'title'},          # Job title\n	'o\
utfile=s'     => \\$params{'outfile'},        # Ou\
tput file name\n	'outformat=s'   => \\$params{'out\
format'},      # Output file type\n	'jobid=s'     \
  => \\$params{'jobid'},          # JobId\n	'help|\
h'        => \\$params{'help'},           # Usage \
help\n	'async'         => \\$params{'async'},     \
     # Asynchronous submission\n	'polljob'       =\
> \\$params{'polljob'},        # Get results\n	're\
sultTypes'   => \\$params{'resultTypes'},    # Get\
 result types\n	'status'        => \\$params{'stat\
us'},         # Get status\n	'params'        => \\\
$params{'params'},         # List input parameters\
\n	'paramDetail=s' => \\$params{'paramDetail'},   \
 # Get details for parameter\n	'quiet'         => \
\\$params{'quiet'},          # Decrease output lev\
el\n	'verbose'       => \\$params{'verbose'},     \
   # Increase output level\n	'debugLevel=i'  => \\\
$params{'debugLevel'},     # Debug output level\n	\
'baseUrl=s'     => \\$baseUrl,                  # \
Base URL for service.\n);\nif ( $params{'verbose'}\
 ) { $outputLevel++ }\nif ( $params{'quiet'} )  { \
$outputLevel-- }\n\n&print_debug_message( 'MAIN', \
'LWP::VERSION: ' . $LWP::VERSION,\n	1 );\n\n&print\
_debug_message( 'MAIN', \"params:\\n\" . Dumper( \\
\%params ),           11 );\n&print_debug_message(\
 'MAIN', \"tool_params:\\n\" . Dumper( \\%tool_par\
ams ), 11 );\n\nmy $ua;\n\nmy $scriptName = basena\
me( $0, () );\n\nif ( $params{'help'} || $numOpts \
== 0 ) {\n	&usage();\n	exit(0);\n}\n\n&print_debug\
_message( 'MAIN', 'baseUrl: ' . $baseUrl, 1 );\n\n\
if (\n	!(\n		   $params{'polljob'}\n		|| $params{'\
resultTypes'}\n		|| $params{'status'}\n		|| $param\
s{'params'}\n		|| $params{'paramDetail'}\n	)\n	&& \
!( defined( $ARGV[0] ) || defined( $params{'sequen\
ce'} ) )\n  )\n{\n\n	# Bad argument combination, s\
o print error message and usage\n	print STDERR 'Er\
ror: bad option combination', \"\\n\";\n	&usage();\
\n	exit(1);\n}\n\nelsif ( $params{'params'} ) {\n	\
&print_tool_params();\n}\n\nelsif ( $params{'param\
Detail'} ) {\n	&print_param_details( $params{'para\
mDetail'} );\n}\n\nelsif ( $params{'status'} && de\
fined( $params{'jobid'} ) ) {\n	&print_job_status(\
 $params{'jobid'} );\n}\n\nelsif ( $params{'result\
Types'} && defined( $params{'jobid'} ) ) {\n	&prin\
t_result_types( $params{'jobid'} );\n}\n\nelsif ( \
$params{'polljob'} && defined( $params{'jobid'} ) \
) {\n	&get_results( $params{'jobid'} );\n}\n\nelse\
 {\n\n	# Multiple input sequence mode, assume fast\
a format.\n	if ( $params{'multifasta'} ) {\n		&mul\
ti_submit_job();\n	}\n\n	# Entry identifier list f\
ile.\n	elsif (( defined( $params{'sequence'} ) && \
$params{'sequence'} =~ m/^\\@/ )\n		|| ( defined( \
$ARGV[0] ) && $ARGV[0] =~ m/^\\@/ ) )\n	{\n		my $l\
ist_filename = $params{'sequence'} || $ARGV[0];\n	\
	$list_filename =~ s/^\\@//;\n		&list_file_submit_\
job($list_filename);\n	}\n\n	# Default: single seq\
uence/identifier.\n	else {\n\n		# Load the sequenc\
e data and submit.\n		&submit_job( &load_data() );\
\n	}\n}\n\n=head1 FUNCTIONS\n\n=cut\n\n\n=head2 re\
st_user_agent()\n\nGet a LWP UserAgent to use to p\
erform REST requests.\n\n  my $ua = &rest_user_age\
nt();\n\n=cut\n\nsub rest_user_agent() {\n	print_d\
ebug_message( 'rest_user_agent', 'Begin', 21 );\n	\
# Create an LWP UserAgent for making HTTP calls.\n\
	my $ua = LWP::UserAgent->new();\n	# Set 'User-Age\
nt' HTTP header to identifiy the client.\n	'$Revis\
ion: 2560 $' =~ m/(\\d+)/;\n	$ua->agent(\"EBI-Samp\
le-Client/$1 ($scriptName; $OSNAME) \" . $ua->agen\
t());\n	# Configure HTTP proxy support from enviro\
nment.\n	$ua->env_proxy;\n	print_debug_message( 'r\
est_user_agent', 'End', 21 );\n	return $ua;\n}\n\n\
=head2 rest_error()\n\nCheck a REST response for a\
n error condition. An error is mapped to a die.\n\\
n  &rest_error($response, $content_data);\n\n=cut\\
n\nsub rest_error() {\n	print_debug_message( 'rest\
_error', 'Begin', 21 );\n	my $response = shift;\n	\
my $contentdata;\n	if(scalar(@_) > 0) {\n		$conten\
tdata = shift;\n	}\n	if(!defined($contentdata) || \
$contentdata eq '') {\n		$contentdata = $response-\
>content();\n	}\n	# Check for HTTP error codes\n	i\
f ( $response->is_error ) {\n		my $error_message =\
 '';\n		# HTML response.\n		if(	$contentdata =~ m/\
<h1>([^<]+)<\\/h1>/ ) {\n			$error_message = $1;\n\
		}\n		#  XML response.\n		elsif($contentdata =~ m\
/<description>([^<]+)<\\/description>/) {\n			$err\
or_message = $1;\n		}\n		die 'http status: ' . $re\
sponse->code . ' ' . $response->message . '  ' . $\
error_message;\n	}\n	print_debug_message( 'rest_er\
ror', 'End', 21 );\n}\n\n=head2 rest_request()\n\n\
Perform a REST request (HTTP GET).\n\n  my $respon\
se_str = &rest_request($url);\n\n=cut\n\nsub rest_\
request {\n	print_debug_message( 'rest_request', '\
Begin', 11 );\n	my $requestUrl = shift;\n	print_de\
bug_message( 'rest_request', 'URL: ' . $requestUrl\
, 11 );\n\n	# Get an LWP UserAgent.\n	$ua = &rest_\
user_agent() unless defined($ua);\n	# Available HT\
TP compression methods.\n	my $can_accept;\n	eval {\
\n	    $can_accept = HTTP::Message::decodable();\n\
	};\n	$can_accept = '' unless defined($can_accept)\
;\n	# Perform the request\n	my $response = $ua->ge\
t($requestUrl,\n		'Accept-Encoding' => $can_accept\
, # HTTP compression.\n	);\n	print_debug_message( \
'rest_request', 'HTTP status: ' . $response->code,\
\n		11 );\n	print_debug_message( 'rest_request',\n\
		'response length: ' . length($response->content(\
)), 11 );\n	print_debug_message( 'rest_request',\n\
		'request:' .\"\\n\" . $response->request()->as_s\
tring(), 32 );\n	print_debug_message( 'rest_reques\
t',\n		'response: ' . \"\\n\" . $response->as_stri\
ng(), 32 );\n	# Unpack possibly compressed respons\
e.\n	my $retVal;\n	if ( defined($can_accept) && $c\
an_accept ne '') {\n	    $retVal = $response->deco\
ded_content();\n	}\n	# If unable to decode use org\
inal content.\n	$retVal = $response->content() unl\
ess defined($retVal);\n	# Check for an error.\n	&r\
est_error($response, $retVal);\n	print_debug_messa\
ge( 'rest_request', 'retVal: ' . $retVal, 12 );\n	\
print_debug_message( 'rest_request', 'End', 11 );\\
n\n	# Return the response data\n	return $retVal;\n\
}\n\n=head2 rest_get_parameters()\n\nGet list of t\
ool parameter names.\n\n  my (@param_list) = &rest\
_get_parameters();\n\n=cut\n\nsub rest_get_paramet\
ers {\n	print_debug_message( 'rest_get_parameters'\
, 'Begin', 1 );\n	my $url                = $baseUr\
l . '/parameters/';\n	my $param_list_xml_str = res\
t_request($url);\n	my $param_list_xml     = XMLin(\
$param_list_xml_str);\n	my (@param_list)       = @\
{ $param_list_xml->{'id'} };\n	print_debug_message\
( 'rest_get_parameters', 'End', 1 );\n	return (@pa\
ram_list);\n}\n\n=head2 rest_get_parameter_details\
()\n\nGet details of a tool parameter.\n\n  my $pa\
ramDetail = &rest_get_parameter_details($param_nam\
e);\n\n=cut\n\nsub rest_get_parameter_details {\n	\
print_debug_message( 'rest_get_parameter_details',\
 'Begin', 1 );\n	my $parameterId = shift;\n	print_\
debug_message( 'rest_get_parameter_details',\n		'p\
arameterId: ' . $parameterId, 1 );\n	my $url      \
            = $baseUrl . '/parameterdetails/' . $p\
arameterId;\n	my $param_detail_xml_str = rest_requ\
est($url);\n	my $param_detail_xml     = XMLin($par\
am_detail_xml_str);\n	print_debug_message( 'rest_g\
et_parameter_details', 'End', 1 );\n	return ($para\
m_detail_xml);\n}\n\n=head2 rest_run()\n\nSubmit a\
 job.\n\n  my $job_id = &rest_run($email, $title, \
\\%params );\n\n=cut\n\nsub rest_run {\n	print_deb\
ug_message( 'rest_run', 'Begin', 1 );\n	my $email \
 = shift;\n	my $title  = shift;\n	my $params = shi\
ft;\n	print_debug_message( 'rest_run', 'email: ' .\
 $email, 1 );\n	if ( defined($title) ) {\n		print_\
debug_message( 'rest_run', 'title: ' . $title, 1 )\
;\n	}\n	print_debug_message( 'rest_run', 'params: \
' . Dumper($params), 1 );\n\n	# Get an LWP UserAge\
nt.\n	$ua = &rest_user_agent() unless defined($ua)\
;\n\n	# Clean up parameters\n	my (%tmp_params) = %\
{$params};\n	$tmp_params{'email'} = $email;\n	$tmp\
_params{'title'} = $title;\n	foreach my $param_nam\
e ( keys(%tmp_params) ) {\n		if ( !defined( $tmp_p\
arams{$param_name} ) ) {\n			delete $tmp_params{$p\
aram_name};\n		}\n	}\n\n	# Submit the job as a POS\
T\n	my $url = $baseUrl . '/run';\n	my $response = \
$ua->post( $url, \\%tmp_params );\n	print_debug_me\
ssage( 'rest_run', 'HTTP status: ' . $response->co\
de, 11 );\n	print_debug_message( 'rest_run',\n		'r\
equest:' .\"\\n\" . $response->request()->as_strin\
g(), 11 );\n	print_debug_message( 'rest_run',\n		'\
response: ' . length($response->as_string()) . \"\\
\n\" . $response->as_string(), 11 );\n\n	# Check f\
or an error.\n	&rest_error($response);\n\n	# The j\
ob id is returned\n	my $job_id = $response->conten\
t();\n	print_debug_message( 'rest_run', 'End', 1 )\
;\n	return $job_id;\n}\n\n=head2 rest_get_status()\
\n\nCheck the status of a job.\n\n  my $status = &\
rest_get_status($job_id);\n\n=cut\n\nsub rest_get_\
status {\n	print_debug_message( 'rest_get_status',\
 'Begin', 1 );\n	my $job_id = shift;\n	print_debug\
_message( 'rest_get_status', 'jobid: ' . $job_id, \
2 );\n	my $status_str = 'UNKNOWN';\n	my $url      \
  = $baseUrl . '/status/' . $job_id;\n	$status_str\
 = &rest_request($url);\n	print_debug_message( 're\
st_get_status', 'status_str: ' . $status_str, 2 );\
\n	print_debug_message( 'rest_get_status', 'End', \
1 );\n	return $status_str;\n}\n\n=head2 rest_get_r\
esult_types()\n\nGet list of result types for fini\
shed job.\n\n  my (@result_types) = &rest_get_resu\
lt_types($job_id);\n\n=cut\n\nsub rest_get_result_\
types {\n	print_debug_message( 'rest_get_result_ty\
pes', 'Begin', 1 );\n	my $job_id = shift;\n	print_\
debug_message( 'rest_get_result_types', 'jobid: ' \
. $job_id, 2 );\n	my (@resultTypes);\n	my $url    \
                  = $baseUrl . '/resulttypes/' . $\
job_id;\n	my $result_type_list_xml_str = &rest_req\
uest($url);\n	my $result_type_list_xml     = XMLin\
($result_type_list_xml_str);\n	(@resultTypes) = @{\
 $result_type_list_xml->{'type'} };\n	print_debug_\
message( 'rest_get_result_types',\n		scalar(@resul\
tTypes) . ' result types', 2 );\n	print_debug_mess\
age( 'rest_get_result_types', 'End', 1 );\n	return\
 (@resultTypes);\n}\n\n=head2 rest_get_result()\n\\
nGet result data of a specified type for a finishe\
d job.\n\n  my $result = rest_get_result($job_id, \
$result_type);\n\n=cut\n\nsub rest_get_result {\n	\
print_debug_message( 'rest_get_result', 'Begin', 1\
 );\n	my $job_id = shift;\n	my $type   = shift;\n	\
print_debug_message( 'rest_get_result', 'jobid: ' \
. $job_id, 1 );\n	print_debug_message( 'rest_get_r\
esult', 'type: ' . $type,    1 );\n	my $url    = $\
baseUrl . '/result/' . $job_id . '/' . $type;\n	my\
 $result = &rest_request($url);\n	print_debug_mess\
age( 'rest_get_result', length($result) . ' charac\
ters',\n		1 );\n	print_debug_message( 'rest_get_re\
sult', 'End', 1 );\n	return $result;\n}\n\n\n=head\
2 print_debug_message()\n\nPrint debug message at \
specified debug level.\n\n  &print_debug_message($\
method_name, $message, $level);\n\n=cut\n\nsub pri\
nt_debug_message {\n	my $function_name = shift;\n	\
my $message       = shift;\n	my $level         = s\
hift;\n	if ( $level <= $params{'debugLevel'} ) {\n\
		print STDERR '[', $function_name, '()] ', $messa\
ge, \"\\n\";\n	}\n}\n\n=head2 print_tool_params()\\
n\nPrint list of tool parameters.\n\n  &print_tool\
_params();\n\n=cut\n\nsub print_tool_params {\n	pr\
int_debug_message( 'print_tool_params', 'Begin', 1\
 );\n	my (@param_list) = &rest_get_parameters();\n\
	foreach my $param ( sort(@param_list) ) {\n		prin\
t $param, \"\\n\";\n	}\n	print_debug_message( 'pri\
nt_tool_params', 'End', 1 );\n}\n\n=head2 print_pa\
ram_details()\n\nPrint details of a tool parameter\
.\n\n  &print_param_details($param_name);\n\n=cut\\
n\nsub print_param_details {\n	print_debug_message\
( 'print_param_details', 'Begin', 1 );\n	my $param\
Name = shift;\n	print_debug_message( 'print_param_\
details', 'paramName: ' . $paramName, 2 );\n	my $p\
aramDetail = &rest_get_parameter_details($paramNam\
e);\n	print $paramDetail->{'name'}, \"\\t\", $para\
mDetail->{'type'}, \"\\n\";\n	print $paramDetail->\
{'description'}, \"\\n\";\n	if(defined($paramDetai\
l->{'values'}->{'value'})) {\n		if(ref($paramDetai\
l->{'values'}->{'value'}) eq 'ARRAY') {\n			foreac\
h my $value ( @{ $paramDetail->{'values'}->{'value\
'} } ) {\n				&print_param_value($value);\n			}\n	\
	}\n		else {\n				&print_param_value($paramDetail-\
>{'values'}->{'value'});\n		}\n	}\n	print_debug_me\
ssage( 'print_param_details', 'End', 1 );\n}\n\n=h\
ead2 print_param_value()\n\nPrint details of a too\
l parameter value.\n\n  &print_param_details($para\
m_value);\n\nUsed by print_param_details() to hand\
le both singluar and array values.\n\n=cut\n\nsub \
print_param_value {\n	my $value = shift;\n	print $\
value->{'value'};\n	if ( $value->{'defaultValue'} \
eq 'true' ) {\n		print \"\\t\", 'default';\n	}\n	p\
rint \"\\n\";\n	print \"\\t\", $value->{'label'}, \
\"\\n\";\n	if ( defined( $value->{'properties'} ) \
) {\n		foreach\n		  my $key ( sort( keys( %{ $valu\
e->{'properties'}{'property'} } ) ) )\n		{\n			if \
( ref( $value->{'properties'}{'property'}{$key} ) \
eq 'HASH'\n				&& defined( $value->{'properties'}{\
'property'}{$key}{'value'} )\n			  )\n			{\n				pr\
int \"\\t\", $key, \"\\t\",\n				  $value->{'prope\
rties'}{'property'}{$key}{'value'}, \"\\n\";\n			}\
\n			else {\n				print \"\\t\", $value->{'properti\
es'}{'property'}{'key'},\n				  \"\\t\", $value->{\
'properties'}{'property'}{'value'}, \"\\n\";\n				\
last;\n			}\n		}\n	}\n}\n\n=head2 print_job_status\
()\n\nPrint status of a job.\n\n  &print_job_statu\
s($job_id);\n\n=cut\n\nsub print_job_status {\n	pr\
int_debug_message( 'print_job_status', 'Begin', 1 \
);\n	my $jobid = shift;\n	print_debug_message( 'pr\
int_job_status', 'jobid: ' . $jobid, 1 );\n	if ( $\
outputLevel > 0 ) {\n		print STDERR 'Getting statu\
s for job ', $jobid, \"\\n\";\n	}\n	my $result = &\
rest_get_status($jobid);\n	print \"$result\\n\";\n\
	if ( $result eq 'FINISHED' && $outputLevel > 0 ) \
{\n		print STDERR \"To get results: $scriptName --\
polljob --jobid \" . $jobid\n		  . \"\\n\";\n	}\n	\
print_debug_message( 'print_job_status', 'End', 1 \
);\n}\n\n=head2 print_result_types()\n\nPrint avai\
lable result types for a job.\n\n  &print_result_t\
ypes($job_id);\n\n=cut\n\nsub print_result_types {\
\n	print_debug_message( 'result_types', 'Begin', 1\
 );\n	my $jobid = shift;\n	print_debug_message( 'r\
esult_types', 'jobid: ' . $jobid, 1 );\n	if ( $out\
putLevel > 0 ) {\n		print STDERR 'Getting result t\
ypes for job ', $jobid, \"\\n\";\n	}\n	my $status \
= &rest_get_status($jobid);\n	if ( $status eq 'PEN\
DING' || $status eq 'RUNNING' ) {\n		print STDERR \
'Error: Job status is ', $status,\n		  '. To get r\
esult types the job must be finished.', \"\\n\";\n\
	}\n	else {\n		my (@resultTypes) = &rest_get_resul\
t_types($jobid);\n		if ( $outputLevel > 0 ) {\n			\
print STDOUT 'Available result types:', \"\\n\";\n\
		}\n		foreach my $resultType (@resultTypes) {\n		\
	print STDOUT $resultType->{'identifier'}, \"\\n\"\
;\n			if ( defined( $resultType->{'label'} ) ) {\n\
				print STDOUT \"\\t\", $resultType->{'label'}, \
\"\\n\";\n			}\n			if ( defined( $resultType->{'de\
scription'} ) ) {\n				print STDOUT \"\\t\", $resu\
ltType->{'description'}, \"\\n\";\n			}\n			if ( d\
efined( $resultType->{'mediaType'} ) ) {\n				prin\
t STDOUT \"\\t\", $resultType->{'mediaType'}, \"\\\
n\";\n			}\n			if ( defined( $resultType->{'fileSu\
ffix'} ) ) {\n				print STDOUT \"\\t\", $resultTyp\
e->{'fileSuffix'}, \"\\n\";\n			}\n		}\n		if ( $st\
atus eq 'FINISHED' && $outputLevel > 0 ) {\n			pri\
nt STDERR \"\\n\", 'To get results:', \"\\n\",\n		\
	  \"  $scriptName --polljob --jobid \" . $params{\
'jobid'} . \"\\n\",\n			  \"  $scriptName --polljo\
b --outformat <type> --jobid \"\n			  . $params{'j\
obid'} . \"\\n\";\n		}\n	}\n	print_debug_message( \
'result_types', 'End', 1 );\n}\n\n=head2 submit_jo\
b()\n\nSubmit a job to the service.\n\n  &submit_j\
ob($seq);\n\n=cut\n\nsub submit_job {\n	print_debu\
g_message( 'submit_job', 'Begin', 1 );\n\n	# Set i\
nput sequence\n	$tool_params{'sequence'} = shift;\\
n\n	# Load parameters\n	&load_params();\n\n	# Subm\
it the job\n	my $jobid = &rest_run( $params{'email\
'}, $params{'title'}, \\%tool_params );\n\n	# Simu\
late sync/async mode\n	if ( defined( $params{'asyn\
c'} ) ) {\n		print STDOUT $jobid, \"\\n\";\n		if (\
 $outputLevel > 0 ) {\n			print STDERR\n			  \"To \
check status: $scriptName --status --jobid $jobid\\
\n\";\n		}\n	}\n	else {\n		if ( $outputLevel > 0 )\
 {\n			print STDERR \"JobId: $jobid\\n\";\n		}\n		\
sleep 1;\n		&get_results($jobid);\n	}\n	print_debu\
g_message( 'submit_job', 'End', 1 );\n}\n\n=head2 \
multi_submit_job()\n\nSubmit multiple jobs assumin\
g input is a collection of fasta formatted sequenc\
es.\n\n  &multi_submit_job();\n\n=cut\n\nsub multi\
_submit_job {\n	print_debug_message( 'multi_submit\
_job', 'Begin', 1 );\n	my $jobIdForFilename = 1;\n\
	$jobIdForFilename = 0 if ( defined( $params{'outf\
ile'} ) );\n	my (@filename_list) = ();\n\n	# Query\
 sequence\n	if ( defined( $ARGV[0] ) ) {    # Bare\
 option\n		if ( -f $ARGV[0] || $ARGV[0] eq '-' ) {\
    # File\n			push( @filename_list, $ARGV[0] );\n\
		}\n		else {\n			warn 'Warning: Input file \"' . \
$ARGV[0] . '\" does not exist'\n		}\n	}\n	if ( $pa\
rams{'sequence'} ) {                   # Via --seq\
uence\n		if ( -f $params{'sequence'} || $params{'s\
equence'} eq '-' ) {    # File\n			push( @filename\
_list, $params{'sequence'} );\n		}\n		else {\n			w\
arn 'Warning: Input file \"' . $params{'sequence'}\
 . '\" does not exist'\n		}\n	}\n\n	$/ = '>';\n	fo\
reach my $filename (@filename_list) {\n		my $INFIL\
E;\n		if($filename eq '-') { # STDIN.\n			open( $I\
NFILE, '<-' )\n			  or die 'Error: unable to STDIN\
 (' . $! . ')';\n		} else { # File.\n			open( $INF\
ILE, '<', $filename )\n			  or die 'Error: unable \
to open file ' . $filename . ' (' . $! . ')';\n		}\
\n		while (<$INFILE>) {\n			my $seq = $_;\n			$seq\
 =~ s/>$//;\n			if ( $seq =~ m/(\\S+)/ ) {\n				pr\
int STDERR \"Submitting job for: $1\\n\"\n				  if\
 ( $outputLevel > 0 );\n				$seq = '>' . $seq;\n		\
		&print_debug_message( 'multi_submit_job', $seq, \
11 );\n				&submit_job($seq);\n				$params{'outfil\
e'} = undef if ( $jobIdForFilename == 1 );\n			}\n\
		}\n		close $INFILE;\n	}\n	print_debug_message( '\
multi_submit_job', 'End', 1 );\n}\n\n=head2 list_f\
ile_submit_job()\n\nSubmit multiple jobs using a f\
ile containing a list of entry identifiers as \nin\
put.\n\n  &list_file_submit_job($list_filename)\n\\
n=cut\n\nsub list_file_submit_job {\n	print_debug_\
message( 'list_file_submit_job', 'Begin', 11 );\n	\
my $filename         = shift;\n	my $jobIdForFilena\
me = 1;\n	$jobIdForFilename = 0 if ( defined( $par\
ams{'outfile'} ) );\n\n	# Iterate over identifiers\
, submitting each job\n	my $LISTFILE;\n	if($filena\
me eq '-') { # STDIN.\n		open( $LISTFILE, '<-' )\n\
		  or die 'Error: unable to STDIN (' . $! . ')';\\
n	} else { # File.\n		open( $LISTFILE, '<', $filen\
ame )\n		  or die 'Error: unable to open file ' . \
$filename . ' (' . $! . ')';\n	}\n	while (<$LISTFI\
LE>) {\n		my $line = $_;\n		chomp($line);\n		if ( \
$line ne '' ) {\n			&print_debug_message( 'list_fi\
le_submit_job', 'line: ' . $line, 2 );\n			if ( $l\
ine =~ m/\\w:\\w/ ) {    # Check this is an identi\
fier\n				print STDERR \"Submitting job for: $line\
\\n\"\n				  if ( $outputLevel > 0 );\n				&submit\
_job($line);\n			}\n			else {\n				print STDERR\n\\
"Warning: line \\\"$line\\\" is not recognised as \
an identifier\\n\";\n			}\n		}\n		$params{'outfile\
'} = undef if ( $jobIdForFilename == 1 );\n	}\n	cl\
ose $LISTFILE;\n	print_debug_message( 'list_file_s\
ubmit_job', 'End', 11 );\n}\n\n=head2 load_data()\\
n\nLoad sequence data from file or option specifie\
d on the command-line.\n\n  &load_data();\n\n=cut\\
n\nsub load_data {\n	print_debug_message( 'load_da\
ta', 'Begin', 1 );\n	my $retSeq;\n\n	# Query seque\
nce\n	if ( defined( $ARGV[0] ) ) {    # Bare optio\
n\n		if ( -f $ARGV[0] || $ARGV[0] eq '-' ) {    # \
File\n			$retSeq = &read_file( $ARGV[0] );\n		}\n	\
	else {                                     # DB:I\
D or sequence\n			$retSeq = $ARGV[0];\n		}\n	}\n	i\
f ( $params{'sequence'} ) {                   # Vi\
a --sequence\n		if ( -f $params{'sequence'} || $pa\
rams{'sequence'} eq '-' ) {    # File\n			$retSeq \
= &read_file( $params{'sequence'} );\n		}\n		else \
{    # DB:ID or sequence\n			$retSeq = $params{'se\
quence'};\n		}\n	}\n	print_debug_message( 'load_da\
ta', 'End', 1 );\n	return $retSeq;\n}\n\n=head2 lo\
ad_params()\n\nLoad job parameters from command-li\
ne options.\n\n  &load_params();\n\n=cut\n\nsub lo\
ad_params {\n	print_debug_message( 'load_params', \
'Begin', 1 );\n\n	# Database(s) to search\n	my (@d\
bList) = split /[ ,]/, $params{'database'};\n	$too\
l_params{'database'} = \\@dbList;\n\n	# Compatabil\
ity options, old command-line.\n	if(!$tool_params{\
'viewfilter'} && $params{'echofilter'}) {\n		$tool\
_params{'viewfilter'} = 'true';\n	}\n	if(!$tool_pa\
rams{'alignments'} && $params{'numal'}) {\n		$tool\
_params{'alignments'} = $params{'numal'};\n	}\n	# \
TODO: set alignment format option to get NCBI BLAS\
T XML.\n	if($params{'appxml'}) {\n		$tool_params{'\
align'} = '';\n	}\n\n	print_debug_message( 'load_p\
arams', 'End', 1 );\n}\n\n=head2 client_poll()\n\n\
Client-side job polling.\n\n  &client_poll($job_id\
);\n\n=cut\n\nsub client_poll {\n	print_debug_mess\
age( 'client_poll', 'Begin', 1 );\n	my $jobid  = s\
hift;\n	my $status = 'PENDING';\n\n	my $errorCount\
 = 0;\n	while ($status eq 'RUNNING'\n		|| $status \
eq 'PENDING'\n		|| ( $status eq 'ERROR' && $errorC\
ount < 2 ) )\n	{\n		$status = rest_get_status($job\
id);\n		print STDERR \"$status\\n\" if ( $outputLe\
vel > 0 );\n		if ( $status eq 'ERROR' ) {\n			$err\
orCount++;\n		}\n		elsif ( $errorCount > 0 ) {\n		\
	$errorCount--;\n		}\n		if (   $status eq 'RUNNING\
'\n			|| $status eq 'PENDING'\n			|| $status eq 'E\
RROR' )\n		{\n\n			# Wait before polling again.\n	\
		sleep $checkInterval;\n		}\n	}\n	print_debug_mes\
sage( 'client_poll', 'End', 1 );\n	return $status;\
\n}\n\n=head2 get_results()\n\nGet the results for\
 a job identifier.\n\n  &get_results($job_id);\n\n\
=cut\n\nsub get_results {\n	print_debug_message( '\
get_results', 'Begin', 1 );\n	my $jobid = shift;\n\
	print_debug_message( 'get_results', 'jobid: ' . $\
jobid, 1 );\n\n	# Verbose\n	if ( $outputLevel > 1 \
) {\n		print 'Getting results for job ', $jobid, \\
"\\n\";\n	}\n\n	# Check status, and wait if not fi\
nished\n	client_poll($jobid);\n\n	# Use JobId if o\
utput file name is not defined\n	unless ( defined(\
 $params{'outfile'} ) ) {\n		$params{'outfile'} = \
$jobid;\n	}\n\n	# Get list of data types\n	my (@re\
sultTypes) = rest_get_result_types($jobid);\n\n	# \
Get the data and write it to a file\n	if ( defined\
( $params{'outformat'} ) ) {    # Specified data t\
ype\n		my $selResultType;\n		foreach my $resultTyp\
e (@resultTypes) {\n			if ( $resultType->{'identif\
ier'} eq $params{'outformat'} ) {\n				$selResultT\
ype = $resultType;\n			}\n		}\n		if ( defined($sel\
ResultType) ) {\n			my $result =\n			  rest_get_re\
sult( $jobid, $selResultType->{'identifier'} );\n	\
		if ( $params{'outfile'} eq '-' ) {\n				write_fi\
le( $params{'outfile'}, $result );\n			}\n			else \
{\n				write_file(\n					$params{'outfile'} . '.'\\
n					  . $selResultType->{'identifier'} . '.'\n		\
			  . $selResultType->{'fileSuffix'},\n					$resu\
lt\n				);\n			}\n		}\n		else {\n			die 'Error: un\
known result format \"' . $params{'outformat'} . '\
\"';\n		}\n	}\n	else {    # Data types available\n\
		      # Write a file for each output type\n		for\
 my $resultType (@resultTypes) {\n			if ( $outputL\
evel > 1 ) {\n				print STDERR 'Getting ', $result\
Type->{'identifier'}, \"\\n\";\n			}\n			my $resul\
t = rest_get_result( $jobid, $resultType->{'identi\
fier'} );\n			if ( $params{'outfile'} eq '-' ) {\n\
				write_file( $params{'outfile'}, $result );\n		\
	}\n			else {\n				write_file(\n					$params{'outf\
ile'} . '.'\n					  . $resultType->{'identifier'} \
. '.'\n					  . $resultType->{'fileSuffix'},\n				\
	$result\n				);\n			}\n		}\n	}\n	print_debug_mess\
age( 'get_results', 'End', 1 );\n}\n\n=head2 read_\
file()\n\nRead a file into a scalar. The special f\
ilename '-' can be used to read from \nstandard in\
put (STDIN).\n\n  my $data = &read_file($filename)\
;\n\n=cut\n\nsub read_file {\n	print_debug_message\
( 'read_file', 'Begin', 1 );\n	my $filename = shif\
t;\n	print_debug_message( 'read_file', 'filename: \
' . $filename, 2 );\n	my ( $content, $buffer );\n	\
if ( $filename eq '-' ) {\n		while ( sysread( STDI\
N, $buffer, 1024 ) ) {\n			$content .= $buffer;\n	\
	}\n	}\n	else {    # File\n		open( my $FILE, '<', \
$filename )\n		  or die \"Error: unable to open in\
put file $filename ($!)\";\n		while ( sysread( $FI\
LE, $buffer, 1024 ) ) {\n			$content .= $buffer;\n\
		}\n		close($FILE);\n	}\n	print_debug_message( 'r\
ead_file', 'End', 1 );\n	return $content;\n}\n\n=h\
ead2 write_file()\n\nWrite data to a file. The spe\
cial filename '-' can be used to write to \nstanda\
rd output (STDOUT).\n\n  &write_file($filename, $d\
ata);\n\n=cut\n\nsub write_file {\n	print_debug_me\
ssage( 'write_file', 'Begin', 1 );\n	my ( $filenam\
e, $data ) = @_;\n	print_debug_message( 'write_fil\
e', 'filename: ' . $filename, 2 );\n	if ( $outputL\
evel > 0 ) {\n		print STDERR 'Creating result file\
: ' . $filename . \"\\n\";\n	}\n	if ( $filename eq\
 '-' ) {\n		print STDOUT $data;\n	}\n	else {\n		op\
en( my $FILE, '>', $filename )\n		  or die \"Error\
: unable to open output file $filename ($!)\";\n		\
syswrite( $FILE, $data );\n		close($FILE);\n	}\n	p\
rint_debug_message( 'write_file', 'End', 1 );\n}\n\
\n=head2 usage()\n\nPrint program usage message.\n\
\n  &usage();\n\n=cut\n\nsub usage {\n	print STDER\
R <<EOF\nWU-BLAST\n========\n   \nRapid sequence d\
atabase search programs utilizing the BLAST algori\
thm\n    \n[Required]\n\n  -p, --program      : st\
r  : BLAST program to use, see --paramDetail progr\
am\n  -D, --database     : str  : database(s) to s\
earch, space separated. See\n                     \
         --paramDetail database\n      --stype    \
    : str  : query sequence type, see --paramDetai\
l stype\n  seqFile            : file : query seque\
nce (\"-\" for STDIN, \\@filename for\n           \
                   identifier list file)\n\n[Optio\
nal]\n\n  -m, --matrix       : str  : scoring matr\
ix, see --paramDetail matrix\n  -e, --exp         \
 : real : 0<E<= 1000. Statistical significance thr\
eshold \n                              for reporti\
ng database sequence matches.\n  -e, --viewfilter \
  :      : display the filtered query sequence\n  \
-f, --filter       : str  : filter the query seque\
nce for low complexity \n                         \
     regions, see --paramDetail filter\n  -A, --al\
ign        : int  : pairwise alignment format, see\
 --paramDetail align\n  -s, --scores       : int  \
: number of scores to be reported\n  -b, --alignme\
nts   : int  : number of alignments to report\n  -\
S, --sensitivity  : str  : sensitivity of the sear\
ch, \n                              see --paramDet\
ail sensitivity\n  -t, --sort	     : str  : sort o\
rder for hits, see --paramDetail sort\n  -T, --sta\
ts        : str  : statistical model, see --paramD\
etail stats\n  -d, --strand       : str  : DNA str\
and to search with,\n                             \
 see --paramDetail strand\n  -c, --topcombon    : \
str  : consistent sets of HSPs\n      --multifasta\
   :      : treat input as a set of fasta formatte\
d sequences\n\n[General]\n\n  -h, --help         :\
      : prints this help text\n      --async      \
  :      : forces to make an asynchronous query\n \
     --email        : str  : e-mail address\n     \
 --title        : str  : title for job\n      --st\
atus       :      : get job status\n      --result\
Types  :      : get available result types for job\
\n      --polljob      :      : poll for the statu\
s of a job\n      --jobid        : str  : jobid th\
at was returned when an asynchronous job \n       \
                       was submitted.\n      --out\
file      : str  : file name for results (default \
is jobid;\n                              \"-\" for\
 STDOUT)\n      --outformat    : str  : result for\
mat to retrieve\n      --params       :      : lis\
t input parameters\n      --paramDetail  : str  : \
display details for input parameter\n      --quiet\
        :      : decrease output\n      --verbose \
     :      : increase output\n   \nSynchronous jo\
b:\n\n  The results/errors are returned as soon as\
 the job is finished.\n  Usage: $scriptName --emai\
l <your\\@email> [options...] seqFile\n  Returns: \
results as an attachment\n\nAsynchronous job:\n\n \
 Use this if you want to retrieve the results at a\
 later time. The results \n  are stored for up to \
24 hours. 	\n  Usage: $scriptName --async --email \
<your\\@email> [options...] seqFile\n  Returns: jo\
bid\n\n  Use the jobid to query for the status of \
the job. If the job is finished, \n  it also retur\
ns the results/errors.\n  Usage: $scriptName --pol\
ljob --jobid <jobId> [--outfile string]\n  Returns\
: string indicating the status of the job and if a\
pplicable, results \n  as an attachment.\n\nFurthe\
r information:\n\n  http://www.ebi.ac.uk/Tools/web\
services/services/sss/wu_blast_rest\n  http://www.\
ebi.ac.uk/Tools/webservices/tutorials/perl\n\nSupp\
ort/Feedback:\n\n  http://www.ebi.ac.uk/support/\n\
EOF\n}\n\n=head1 FEEDBACK/SUPPORT\n\nPlease contac\
t us at L<http://www.ebi.ac.uk/support/> if you ha\
ve any \nfeedback, suggestions or issues with the \
service or this client.\n\n=cut\n","\n\n\nmy $PROB\
TRESH = 0.3;# base pairs below this prob threshold\
 will be ignored\nmy $WEIGHT = 100.0; # float!!\nm\
y $NUCALPH = \"ACGTUNRYMKSWHBVD\";\nuse vars qw($N\
UCALPH $WEIGHT);\n\nmy $myname = basename($0);\n\n\
use strict;\nuse warnings;\n\nuse File::Basename;\\
nuse Getopt::Long;\nuse File::Glob ':glob';\nuse F\
ile::Spec;\nuse File::Temp qw/ tempfile tempdir /;\
\n\n\n\n\nsub tcoffeelib_header($;$)\n{\n    my ($\
nseq, $fd) = @_;\n    if (! defined($fd)) {\n     \
   $fd = *STDOUT;\n    }\n    printf $fd \"! TC_LI\
B_FORMAT_01\\n\";\n    printf $fd \"%d\\n\", $nseq\
;\n}\n\n\nsub tcoffeelib_header_addseq($$;$)\n{\n \
   my ($id, $seq, $fd) = @_;\n    if (! defined($f\
d)) {\n        $fd = *STDOUT;\n    }\n    printf $\
fd \"%s %d %s\\n\", $id, length($seq), $seq;\n}\n\\
n\nsub tcoffeelib_comment($;$)\n{\n    my ($commen\
t, $fd) = @_;\n    if (! defined($fd)) {\n        \
$fd = *STDOUT;\n    }\n    printf $fd \"!\" . $com\
ment . \"\\n\";\n}\n\n\nsub tcoffeelib_struct($$$;\
$)\n{\n    my ($nseq, $len, $bpm, $fd) = @_;\n\n  \
  if (! defined($fd)) {\n        $fd = *STDOUT;\n \
   }\n\n    # output basepair indices with fixed w\
eight\n    printf $fd \"#%d %d\\n\", $nseq, $nseq;\
\n    # output basepairs (only once) and with unit\
-offset\n    for (my $i=0; $i<$len; $i++) {\n     \
   for (my $j=$i+1; $j<$len; $j++) {\n            \
if (! defined($bpm->[$i][$j])) {\n                \
print STDERR \"ERROR: \\$bpm->[$i][$j] undefined\\\
n\";\n            }\n            if ($bpm->[$i][$j\
]>0) {\n                print $fd $i+1;\n         \
       print $fd \" \";\n                print $fd\
 $j+1;\n                print $fd \" \" . $bpm->[$\
i][$j] . \"\\n\";\n            }\n        }\n    }\
\n}\n\n\nsub tcoffeelib_footer(;$)\n{\n    my ($fd\
) = @_;\n    if (! defined($fd)) {\n        $fd = \
*STDOUT;\n    }\n    print $fd \"! SEQ_1_TO_N\\n\"\
;\n}\n\n\n    \nsub plfold($$$)\n{    \n    my ($i\
d, $seq, $probtresh) = @_;\n    my (@struct);# ret\
urn\n    my ($templ, $fhtmp, $fnametmp, $cmd, $ctr\
, $window_size);\n    our $ntemp++;\n    \n    $te\
mpl = $myname . \".pid-\" . $$ .$ntemp .\".XXXXXX\\
";\n    ($fhtmp, $fnametmp) = tempfile($templ, UNL\
INK => 1); \n    print $fhtmp \">$id\\n$seq\\n\";\\
n\n    # --- init basepair array\n    #\n    for (\
my $i=0; $i<length($seq); $i++) {\n        for (my\
 $j=$i+1; $j<length($seq); $j++) {\n            $s\
truct[$i][$j]=0;\n        }\n    }\n\n\n    # --- \
call rnaplfold and drop a readme\n    #\n    $wind\
ow_size=(length($seq)<70)?length($seq):70;\n    $c\
md = \"RNAplfold -W $window_size < $fnametmp >/dev\
/null\";\n    system($cmd);\n    \n    if ($? != 0\
) {\n        printf STDERR \"ERROR: RNAplfold ($cm\
d) exited with error status %d\\n\", $? >> 8;\n   \
     return;\n    }\n    #unlink($fnametmp);\n    \
my $fps = sprintf(\"%s_dp.ps\", $id); # check long\
 name\n    \n    if (! -s $fps) {\n      {\n\n	$fp\
s = sprintf(\"%s_dp.ps\", substr($id,0,12)); # che\
ck short name\n 	if (! -s $fps)\n	  {\n	    die(\"\
couldn't find expected file $fps\\n\");\n	    retu\
rn;\n	  }\n      }\n    }\n\n    \n    # --- read \
base pairs from created postscript\n    #\n    ope\
n(FH, $fps);\n    while (my $line = <FH>) {\n     \
   my ($nti, $ntj, $prob);\n        chomp($line); \
       \n        # line: bp bp sqrt-prob ubox\n   \
     my @match = ($line =~ m/^([0-9]+) +([0-9]+) +\
([0-9\\.]+) +ubox$/);\n        if (scalar(@match))\
 {\n            $nti=$1;\n            $ntj=$2;\n  \
          $prob=$3*$3;# prob stored as square root\
\n\n            if ($prob>$probtresh) {\n         \
       #printf STDERR \"\\$struct[$nti][$ntj] sqrt\
prob=$3 prob=$prob > $probtresh\\n\";\n           \
     $struct[$nti-1][$ntj-1] = $WEIGHT\n          \
  }\n            # store with zero-offset\n       \
 }\n    }\n    close(FH);\n\n    # remove or gzi p\
ostscript\n    #\n    unlink($fps);\n    #\n    # \
or gzip\n    #$cmd = \"gzip -qf $fps\";\n    #syst\
em($cmd);\n    #if ($? != 0) {\n    #    printf ST\
DERR \"ERROR: gzip ($cmd) exited with error status\
 %d\\n\", $? >> 8;\n    #}\n\n    return \\@struct\
;\n}\n\n\n\n\n\nsub rnaseqfmt($)\n{\n    my ($seq)\
 = @_;\n    # remove gaps\n    $seq =~ s/-//g;\n  \
  # uppercase RNA\n    $seq = uc($seq);\n    # T -\
> U\n    $seq =~ s/T/U/g;\n    # check for invalid\
 charaters\n    $_ = $seq;\n    s/[^$NUCALPH]//g;\\
n    return $_;\n}\n\n\n\n\nsub usage(;$)\n{    \n\
    my ($errmsg) = @_;\n    if ($errmsg) {\n      \
  print STDERR \"ERROR: $errmsg\\n\";\n    }\n    \
print STDERR << \"EOF\";\n$myname:\n Creates a T-C\
offee RNA structure library from RNAplfold predict\
ion.\n See FIXME:citation\nUsage:\n $myname -in se\
q_file -out tcoffee_lib\nEOF\n    exit(1);\n}\n\ns\
ub read_fasta_seq \n  {\n    my $f=$_[0];\n    my \
%hseq;\n    my (@seq, @com, @name);\n    my ($a, $\
s,$nseq);\n\n    open (F, $f);\n    while (<F>)\n \
     {\n	$s.=$_;\n      }\n    close (F);\n\n    \\
n    @name=($s=~/>(\\S*).*\\n[^>]*/g);\n    \n    \
@seq =($s=~/>.*.*\\n([^>]*)/g);\n    @com =($s=~/>\
(\\S*)(.*)\\n([^>]*)/g);\n\n\n    $nseq=$#name+1;\\
n  \n    for ($a=0; $a<$nseq; $a++)\n      {\n	my \
$n=$name[$a];\n	my $s;\n	$hseq{$n}{name}=$n;\n	$s=\
$seq[$a];$s=~s/\\s//g;\n	\n	$hseq{$n}{seq}=$s;\n	$\
hseq{$n}{com}=$com[$a];\n      }\n    return %hseq\
;\n  }\n\n\n\n\n\n\n\nmy $fmsq = \"\";\nmy $flib =\
 \"\";\nmy %OPTS;\nmy %seq;\nmy ($id, $nseq, $i);\\
nmy @nl;\n\nGetOptions(\"in=s\" => \\$fmsq, \"out=\
s\" => \\$flib);\n\nif (! -s $fmsq) {\n    usage(\\
"empty or non-existant file \\\"$fmsq\\\"\")\n}\ni\
f (length($flib)==0) {\n    usage(\"empty out-file\
name\")\n}\n\n\n\n\n\n\n%seq=read_fasta_seq($fmsq)\
;\n\n\n@nl=keys(%seq);\n\n$nseq=$#nl+1;\nopen FD_L\
IB, \">$flib\" or die \"can't open $flib!\";\ntcof\
feelib_header($nseq, *FD_LIB);\nforeach $id (keys \
(%seq))\n  {\n    my ($seq, $fmtseq);\n    \n    $\
seq = $seq{$id}{seq};\n    \n    $fmtseq = rnaseqf\
mt($seq);# check here, formatting for folding impo\
rtant later\n    if (length($seq)!=length($fmtseq)\
) {\n        print STDERR \"ERROR: invalid sequenc\
e $id is not an RNA sequence. read seq is: $seq\\n\
\";\n        exit\n      }\n   \n    tcoffeelib_he\
ader_addseq($id, uc($seq), *FD_LIB);\n  }\ntcoffee\
lib_comment(\"generated by $myname on \" . localti\
me(), *FD_LIB);\n\n\n\n$i=0;\nforeach $id (keys (%\
seq))\n  {\n    my ($cleanid, $seq, $bpm);\n    $s\
eq=$seq{$id}{seq};\n    $cleanid = $id;\n    $clea\
nid =~ s,[/ ],_,g;# needed for rnaplfold\n    $seq\
 = rnaseqfmt($seq);\n    \n    $bpm = plfold($clea\
nid, rnaseqfmt($seq), $PROBTRESH);       \n    \n \
   tcoffeelib_struct($i+1, length($seq), $bpm, *FD\
_LIB);\n    $i++;\n}\n\n\ntcoffeelib_footer(*FD_LI\
B);\nclose FD_LIB;\nexit (0);\n\n","\n\n\n\n\n$cmd\
=join ' ', @ARGV;\nif ($cmd=~/-infile=(\\S+)/){ $s\
eqfile=$1;}\nif ($cmd=~/-outfile=(\\S+)/){ $libfil\
e=$1;}\n\n\n\n%s=read_fasta_seq ($seqfile);\n\nope\
n (F, \">$libfile\");\nforeach $name (keys (%s))\n\
  {\n    my $tclib=\"$name.RNAplfold_tclib\";\n   \
 print (F \">$name _F_ $tclib\\n\");\n    seq2RNAp\
lfold2tclib ($name, $s{$name}{seq}, $tclib);\n  }\\
nclose (F);\nexit (EXIT_SUCCESS);\n\nsub seq2RNApl\
fold2tclib\n  {\n    my ($name, $seq, $tclib)=@_;\\
n    my ($tmp);\n    $n++;\n    $tmp=\"tmp4seq2RNA\
plfold_tclib.$$.$n.pep\";\n    open (RF, \">$tmp\"\
);\n    print (RF \">$name\\n$seq\\n\");\n    clos\
e (RF);\n    \n    system \"t_coffee -other_pg RNA\
plfold2tclib.pl -in=$tmp -out=$tclib\";\n    \n   \
 unlink ($tmp);\n    return $tclib;\n  }\n    \n  \
  \nsub read_fasta_seq \n  {\n    my $f=@_[0];\n  \
  my %hseq;\n    my (@seq, @com, @name);\n    my (\
$a, $s,$nseq);\n\n    open (F, $f);\n    while (<F\
>)\n      {\n	$s.=$_;\n      }\n    close (F);\n\n\
    \n    @name=($s=~/>(\\S*).*\\n[^>]*/g);\n    \\
n    @seq =($s=~/>.*.*\\n([^>]*)/g);\n    @com =($\
s=~/>\\S*(.*)\\n([^>]*)/g);\n\n    \n    $nseq=$#n\
ame+1;\n    \n    for ($a=0; $a<$nseq; $a++)\n    \
  {\n	my $n=$name[$a];\n	$hseq{$n}{name}=$n;\n	$hs\
eq{$n}{seq}=$seq[$a];\n	$hseq{$n}{com}=$com[$a];\n\
      }\n    return %hseq;\n  }\n","use Getopt::Lo\
ng;\nuse File::Path;\nuse Env;\nuse FileHandle;\nu\
se Cwd;\nuse Sys::Hostname;\nour $PIDCHILD;\nour $\
ERROR_DONE;\nour @TMPFILE_LIST;\nour $EXIT_FAILURE\
=1;\nour $EXIT_SUCCESS=0;\n\nour $REFDIR=getcwd;\n\
our $EXIT_SUCCESS=0;\nour $EXIT_FAILURE=1;\n\nour \
$PROGRAM=\"tc_generic_method.pl\";\nour $CL=$PROGR\
AM;\n\nour $CLEAN_EXIT_STARTED;\nour $debug_lock=$\
ENV{\"DEBUG_LOCK\"};\nour $LOCKDIR=$ENV{\"LOCKDIR_\
4_TCOFFEE\"};\nif (!$LOCKDIR){$LOCKDIR=getcwd();}\\
nour $ERRORDIR=$ENV{\"ERRORDIR_4_TCOFFEE\"};\nour \
$ERRORFILE=$ENV{\"ERRORFILE_4_TCOFFEE\"};\n&set_lo\
ck ($$);\nif (isshellpid(getppid())){lock4tc(getpp\
id(), \"LLOCK\", \"LSET\", \"$$\\n\");}\n      \no\
ur $print;\nmy ($fmsq1, $fmsq2, $output, $outfile,\
 $arch, $psv, $hmmtop_home, $trim, $cov, $sample, \
$mode, $gor_home, $gor_seq, $gor_obs);\n\nGetOptio\
ns(\"-in=s\" => \\$fmsq1,\"-output=s\" =>\\$output\
 ,\"-out=s\" => \\$outfile, \"-arch=s\" => \\$arch\
,\"-psv=s\" => \\$psv, \"-hmmtop_home=s\", \\$hmmt\
op_home,\"-trim=s\" =>\\$trim ,\"-print=s\" =>\\$p\
rint,\"-cov=s\" =>\\$cov , \"-sample=s\" =>\\$samp\
le, \"-mode=s\" =>\\$mode, \"-gor_home=s\"=>\\$gor\
_home, \"-gor_seq=s\"=>\\$gor_seq,\"-gor_obs=s\"=>\
\\$gor_obs);\n\n\nif (!$mode){$mode = \"hmmtop\"}\\
nelsif ($mode eq \"hmmtop\"){;}\nelsif ($mode eq \\
"gor\"){;}\nelse {myexit(flush_error (\"-mode=$mod\
e is unknown\"));}\n\n\nour $HOME=$ENV{\"HOME\"};\\
nour $MCOFFEE=($ENV{\"MCOFFEE_4_TCOFFEE\"})?$ENV{\\
"MCOFFEE_4_TCOFFEE\"}:\"$HOME/.t_coffee/mcoffee\";\
\n\nif ($mode eq \"hmmtop\")\n  {\n    check_confi\
guration (\"hmmtop\");\n    if (-e $arch){$ENV{'HM\
MTOP_ARCH'}=$arch;}\n    elsif (-e $ENV{HMMTOP_ARC\
H}){$arch=$ENV{HMMTOP_ARCH};}\n    elsif (-e \"$MC\
OFFEE/hmmtop.arch\"){$arch=$ENV{'HMMTOP_ARCH'}=\"$\
MCOFFEE/hmmtop.arch\";}\n    elsif (-e \"$hmmtop_h\
ome/hmmtop.arc\"){$arch=$ENV{'HMMTOP_ARCH'}=\"$hmm\
top_home/hmmtop.arc\";}\n    else {myexit(flush_er\
ror ( \"Could not find ARCH file for hmmtop\"));}\\
n    \n    \n    if (-e $psv){$ENV{'HMMTOP_PSV'}=$\
psv;}\n    elsif (-e $ENV{HMMTOP_PSV}){$psv=$ENV{H\
MMTOP_PSV};}\n    elsif (-e \"$MCOFFEE/hmmtop.psv\\
"){$psv=$ENV{'HMMTOP_PSV'}=\"$MCOFFEE/hmmtop.psv\"\
;}\n    elsif (-e \"$hmmtop_home/hmmtop.psv\"){$ps\
v=$ENV{'HMMTOP_PSV'}=\"$hmmtop_home/hmmtop.psv\";}\
\n    else {myexit(flush_error ( \"Could not find \
PSV file for hmmtop\"));}\n  }\nelsif ($mode eq \"\
gor\")\n  {\n    our $GOR_SEQ;\n    our $GOR_OBS;\\
n    \n    check_configuration (\"gorIV\");\n    i\
f (-e $gor_seq){$GOR_SEQ=$gor_seq;}\n    elsif (-e\
 $ENV{GOR_SEQ}){$GOR_SEQ=$ENV{GOR_SEQ};}\n    elsi\
f (-e \"$MCOFFEE/New_KS.267.seq\"){$GOR_SEQ=\"$MCO\
FFEE/New_KS.267.seq\";}\n    elsif (-e \"$gor_home\
/New_KS.267.seq\"){$GOR_SEQ=\"$gor_home/New_KS.267\
.seq\";}\n    else {myexit(flush_error ( \"Could n\
ot find SEQ file for gor\"));}\n\n    if (-e $gor_\
obs){$GOR_OBS=$gor_obs;}\n    elsif (-e $ENV{GOR_O\
BS}){$GOR_OBS=$ENV{GOR_OBS};}\n    elsif (-e \"$MC\
OFFEE/New_KS.267.obs\"){$GOR_OBS=\"$MCOFFEE/New_KS\
.267.obs\";}\n    elsif (-e \"$gor_home/New_KS.267\
.obs\"){$GOR_OBS=\"$gor_home/New_KS.267.obs\";}\n \
   else {myexit(flush_error ( \"Could not find OBS\
 file for gor\"));}\n  }\n\n\nif ( ! -e $fmsq1){my\
exit(flush_error (\"Could Not Read Input file $fms\
q1\"));}\n\n\nmy $fmsq2=vtmpnam();\nmy $fmsq3=vtmp\
nam();\nmy $tmpfile=vtmpnam();\nmy $predfile=vtmpn\
am();\n\nif ($trim){$trim_action=\" +trim _aln_%%$\
trim\\_K1 \";}\nif ($cov) {$cov_action= \" +sim_fi\
lter _aln_c$cov \";}\n&safe_system(\"t_coffee -oth\
er_pg seq_reformat -in $fmsq1 -action +convert 'BO\
UJXZ-' $cov_action $trim_action -output fasta_aln \
-out $fmsq2\");\nmy (%pred, %seq, %predA);\n\n\n%s\
eq=read_fasta_seq($fmsq2);\n%seq=fasta2sample(\\%s\
eq, $sample);\n\nif (1==2 && $mode eq \"hmmtop\" &\
& $output eq \"cons\")\n  {\n    fasta2hmmtop_cons\
($outfile,\\%seq);\n  }\nelse\n  {\n    %pred=fast\
a2pred(\\%seq, $mode);\n    %predA=pred2aln (\\%pr\
ed, \\%seq);\n    \n    \n    if (!$output || $out\
put eq \"prediction\"){output_fasta_seq (\\%predA,\
 $outfile);}\n    elsif ($output eq \"color_html\"\
){pred2color (\\%pred,\\%seq, $outfile);}\n    els\
if ($output eq \"cons\"){pred2cons($outfile,\\%pre\
dA);}\n    else {flush_error (\"$output is an unkn\
own output mode\");}\n  }\n\nsub fasta2sample\n  {\
\n    my $SR=shift;\n    my $it=shift;\n    my %S=\
%$SR;\n    \n    my $seq=index2seq_name (\\%S, 1);\
\n    my $l=length($S{$seq}{seq});\n    my @sl=key\
s(%S);\n    my $nseq=$#sl+1;\n    my $index=$nseq;\
\n  \n    if (!$sample) {return %S;}\n    for (my \
$a=0; $a<$it; $a++)\n      {\n	my $newseq=\"\";\n	\
my $nname=\"$seq\\_sampled_$index\";\n	for (my $p=\
0; $p<$l; $p++)\n	  {\n	    my $i=int(rand($nseq))\
;\n	    \n	    my $name = $sl[$i];\n	    my $seq=$\
S{$name}{seq};\n	    my $r=substr ($seq, $p, 1);\n\
	    $newseq.=$r;\n	  }\n	$S{$nname}{name}=$nname;\
\n	$S{$nname}{seq}=$newseq;\n	$S{$nname}{com}=\"sa\
mpled\";\n	$S{$nname}{index}=++$index;\n      }\n \
   return %S;\n  }\n	      \nsub fasta2pred\n  {\n\
    my $s=shift;\n    my $mode=shift;\n\n    if ( \
$mode eq \"hmmtop\"){return fasta2hmmtop_pred($s);\
}\n    elsif ($mode eq \"gor\"){return fasta2gor_p\
red ($s);}\n  }\nsub fasta2hmmtop_cons\n  {\n    m\
y $outfile=shift;\n    my $SR=shift;\n    \n    my\
 $o = new FileHandle;\n    my $i = new FileHandle;\
\n    my $tmp_in =vtmpnam();\n    my $tmp_out=vtmp\
nam();\n    my %seq=%$SR;\n    my %pred;\n    my $\
N=keys(%seq);\n    \n    output_fasta_seq (\\%seq,\
$tmp_in, \"seq\");\n    `hmmtop -pi=mpred -if=$tmp\
_in -sf=FAS -pl 2>/dev/null >$tmp_out`;\n    open \
($o, \">$outfile\");\n    open ($i, \"$tmp_out\");\
\n    while (<$i>)\n      {\n	my $l=$_;\n	if (($l=\
~/>HP\\:\\s+(\\d+)\\s+(.*)/)){my $line=\">$2 NSEQ:\
 $N\\n\";print $o \"$line\";}\n	elsif ( ($l=~/.*pr\
ed(.*)/))  {my $line=\"$1\\n\";print $o \"$line\";\
}\n      }\n    close ($o);\n    close ($i);\n    \
return read_fasta_seq($tmp);\n  }\nsub fasta2hmmto\
p_pred\n  {\n    my $SR=shift;\n    my $o = new Fi\
leHandle;\n    my $i = new FileHandle;\n    my $tm\
p    =vtmpnam();\n    my $tmp_in =vtmpnam();\n    \
my $tmp_out=vtmpnam();\n    my %seq=%$SR;\n    my \
%pred;\n    \n\n    output_fasta_seq (\\%seq,$tmp_\
in, \"seq\");\n    `hmmtop -if=$tmp_in -sf=FAS -pl\
 2>/dev/null >$tmp_out`;\n    open ($o, \">$tmp\")\
;\n    open ($i, \"$tmp_out\");\n    while (<$i>)\\
n      {\n	my $l=$_;\n	if (($l=~/>HP\\:\\s+(\\d+)\\
\s+(.*)/)){my $line=\">$2\\n\";print $o \"$line\";\
}\n	elsif ( ($l=~/.*pred(.*)/))  {my $line=\"$1\\n\
\";print $o \"$line\";}\n      }\n    close ($o);\\
n    close ($i);\n    return read_fasta_seq($tmp);\
\n  }\n    \n	\n	\n	    \n	\n	\n\n	\nsub fasta2gor\
_pred\n  {\n    my $SR=shift;\n    my $o = new Fil\
eHandle;\n    my $i = new FileHandle;\n    my $tmp\
    =vtmpnam();\n    my $tmp_in =vtmpnam();\n    m\
y $tmp_out=vtmpnam();\n    my %seq=%$SR;\n    my %\
pred;\n    \n\n    output_fasta_seq (\\%seq,$tmp_i\
n, \"seq\");\n    `gorIV -prd $tmp_in -seq $GOR_SE\
Q -obs $GOR_OBS >$tmp_out`;\n    open ($o, \">$tmp\
\");\n    open ($i, \"$tmp_out\");\n    while (<$i\
>)\n      {\n	my $l=$_;\n\n	\n	if ( $l=~/>/){print\
 $o \"$l\";}\n	elsif ( $l=~/Predicted Sec. Struct.\
/){$l=~s/Predicted Sec. Struct\\.//;print $o \"$l\\
";}\n      }\n    close ($o);\n    close ($i);\n  \
  return read_fasta_seq($tmp);\n  }\n			\n			     \
\nsub index2seq_name\n  {\n    \n    my $SR=shift;\
\n    my $index=shift;\n    \n    \n    my %S=%$SR\
;\n    \n    foreach my $s (%S)\n      {\n	if ( $S\
{$s}{index}==$index){return $s;}\n      }\n    ret\
urn \"\";\n  }\n\nsub pred2cons\n  {\n    my $outf\
ile=shift;\n    my $predR=shift;\n    my $seq=shif\
t;\n    my %P=%$predR;\n    my %C;\n    my ($s,@r,\
$nseq);\n    my $f= new FileHandle;\n\n    open ($\
f, \">$outfile\");\n\n    if (!$seq){$seq=index2se\
q_name(\\%P,1);}\n    foreach my $s (keys(%P))\n  \
    {\n	$nseq++;\n	$string= $P{$s}{seq};\n	$string\
 = uc $string;\n	my @r=split (//,$string);\n	for (\
my $a=0; $a<=$#r; $a++)\n	  {\n	    if (($r[$a]=~/\
[OHICE]/)){$C{$a}{$r[$a]}++;}\n	  }\n      }\n    \
@l=keys(%C);\n    \n    \n    $s=$P{$seq}{seq};\n \
   print $f \">$seq pred based on $nseq\\n\";\n   \
 @r=split (//,$s);\n    \n    for (my $x=0; $x<=$#\
r; $x++)\n      {\n	if ($r[$x] ne \"-\")\n	  {\n	 \
   my $h=$C{$x}{H};\n	    my $i=$C{$x}{I};\n	    m\
y $o=$C{$x}{O};\n	    my $c=$C{$x}{C};\n	    my $e\
=$C{$x}{E};\n	    my $l=$i+$o;\n	    \n	    if ($h\
>=$i && $h>=$o && $h>=$c && $h>=$e){$r[$x]='H';}\n\
	    elsif ($i>=$o && $i>=$c && $i>=$e){$r[$x]='I'\
;}\n	    elsif ($o>=$c && $o>=$e){$r[$x]='O';}\n	 \
   elsif ($c>=$e){$r[$x]='C';}\n	    else {$r[$x]=\
'E';}\n	  }\n      }\n    $j=join ('', @r);\n    p\
rint $f \"$j\\n\";\n    close ($f);\n    return $j\
;\n  }\n\nsub pred2aln\n  {\n    my $PR=shift;\n  \
  my $AR=shift;\n    \n    my $f=new FileHandle;\n\
    my %P=%$PR;\n    my %A=%$AR;\n    my %PA;\n   \
 my $tmp=vtmpnam();\n    my $f= new FileHandle;\n \
   \n    open ($f, \">$tmp\");\n    foreach my $s \
(sort{$A{$a}{index}<=>$A{$b}{index}}(keys (%A)))\n\
      {\n	my (@list, $seq, @plist, @pseq, $L, $PL,\
 $c, $w);\n	my $seq;\n	my $seq=$A{$s}{seq};\n	my $\
pred=$P{$s}{seq};\n	$seq=pred2alnS($P{$s}{seq},$A{\
$s}{seq});\n	print $f \">$s\\n$seq\\n\";\n      }\\
n    close ($f);\n    return read_fasta_seq ($tmp)\
;\n  }\nsub pred2alnS\n  {\n    my $pred=shift;\n \
   my $aln= shift;\n    my ($j,$a,$b);\n    my @P=\
split (//, $pred);\n    my @A=split (//, $aln);\n \
   for ($a=$b=0;$a<=$#A; $a++)\n      {\n	if ($A[$\
a] ne \"-\"){$A[$a]=$P[$b++];}\n      }\n    if ($\
b!= ($#P+1)){add_warning (\"Could not thread seque\
nce: $b $#P\");}\n    \n    $j= join ('', @A);\n  \
  return $j;\n  }\nsub pred2color\n  {\n    my $pr\
edP=shift;\n    my $alnP=shift;\n    my $out=shift\
;\n    my $F=new FileHandle;\n    my $struc=vtmpna\
m();\n    my $aln=vtmpnam();\n    \n\n    output_f\
asta_seq ($alnP, $aln);\n    my %p=%$predP;\n    \\
n    open ($F, \">$struc\");\n    \n    \n    fore\
ach my $s (keys(%p))\n      {\n	\n	print $F \">$s\\
\n\";\n	my $s=uc($p{$s}{seq});\n	\n	$s=~s/[Oo]/0/g\
;\n	$s=~s/[Ee]/0/g;\n	\n	$s=~s/[Ii]/5/g;\n	$s=~s/[\
Cc]/5/g;\n	\n	$s=~s/[Hh]/9/g;\n	\n	print $F \"$s\\\
n\";\n      }\n    close ($F);\n    \n    \n    \n\
    safe_system ( \"t_coffee -other_pg seq_reforma\
t -in $aln -struc_in $struc -struc_in_f number_fas\
ta -output color_html -out $out\");\n    return;\n\
  }\n	  \n    \nsub display_fasta_seq\n  {\n    my\
 $SR=shift;\n    my %S=%$SR;\n    \n    foreach my\
 $s (sort{$S{$a}{index}<=>$S{$b}{index}}(keys (%S)\
))\n      {\n	print STDERR \">$s\\n$S{$s}{seq}\\n\\
";\n      }\n    close ($f);\n  }\nsub output_fast\
a_seq\n  {\n    my $SR=shift;\n    my $outfile=shi\
ft;\n    my $mode =shift;\n    my $f= new FileHand\
le;\n    my %S=%$SR;\n    \n    \n    open ($f, \"\
>$outfile\");\n    foreach my $s (sort{$S{$a}{inde\
x}<=>$S{$b}{index}}(keys (%S)))\n      {\n	my $seq\
=$S{$s}{seq};\n	if ( $mode eq \"seq\"){$seq=~s/\\-\
//g;}\n	print $f \">$s\\n$seq\\n\";\n      }\n    \
close ($f);\n  }\n      \nsub read_fasta_seq \n  {\
\n    my $f=$_[0];\n    my %hseq;\n    my (@seq, @\
com, @name);\n    my ($a, $s,$nseq);\n    my $inde\
x;\n    open (F, $f);\n    while (<F>)\n      {\n	\
$s.=$_;\n      }\n    close (F);\n\n    \n    @nam\
e=($s=~/>(\\S*).*\\n[^>]*/g);\n    \n    @seq =($s\
=~/>.*.*\\n([^>]*)/g);\n    @com =($s=~/>.*(.*)\\n\
([^>]*)/g);\n\n\n    $nseq=$#name+1;\n    \n  \n  \
  for ($a=0; $a<$nseq; $a++)\n      {\n	my $n=$nam\
e[$a];\n	my $s;\n	$hseq{$n}{name}=$n;\n	$s=$seq[$a\
];$s=~s/\\s//g;\n	$hseq{$n}{index}=++$index;\n	$hs\
eq{$n}{seq}=$s;\n	$hseq{$n}{com}=$com[$a];\n      \
}\n    return %hseq;\n  }\n\n\nsub file2head\n    \
  {\n	my $file = shift;\n	my $size = shift;\n	my $\
f= new FileHandle;\n	my $line;\n	open ($f,$file);\\
n	read ($f,$line, $size);\n	close ($f);\n	return $\
line;\n      }\nsub file2tail\n      {\n	my $file \
= shift;\n	my $size = shift;\n	my $f= new FileHand\
le;\n	my $line;\n	\n	open ($f,$file);\n	seek ($f,$\
size*-1, 2);\n	read ($f,$line, $size);\n	close ($f\
);\n	return $line;\n      }\n\n\nsub vtmpnam\n    \
  {\n	my $r=rand(100000);\n	my $f=\"file.$r.$$\";\\
n	while (-e $f)\n	  {\n	    $f=vtmpnam();\n	  }\n	\
push (@TMPFILE_LIST, $f);\n	return $f;\n      }\n\\
nsub myexit\n  {\n    my $code=@_[0];\n    if ($CL\
EAN_EXIT_STARTED==1){return;}\n    else {$CLEAN_EX\
IT_STARTED=1;}\n    ### ONLY BARE EXIT\n    exit (\
$code);\n  }\nsub set_error_lock\n    {\n      my \
$name = shift;\n      my $pid=$$;\n\n      \n     \
 &lock4tc ($$,\"LERROR\", \"LSET\", \"$$ -- ERROR:\
 $name $PROGRAM\\n\");\n      return;\n    }\nsub \
set_lock\n  {\n    my $pid=shift;\n    my $msg= sh\
ift;\n    my $p=getppid();\n    &lock4tc ($pid,\"L\
LOCK\",\"LRESET\",\"$p$msg\\n\");\n  }\nsub unset_\
lock\n   {\n     \n    my $pid=shift;\n    &lock4t\
c ($pid,\"LLOCK\",\"LRELEASE\",\"\");\n  }\nsub sh\
ift_lock\n  {\n    my $from=shift;\n    my $to=shi\
ft;\n    my $from_type=shift;\n    my $to_type=shi\
ft;\n    my $action=shift;\n    my $msg;\n    \n  \
  if (!&lock4tc($from, $from_type, \"LCHECK\", \"\\
")){return 0;}\n    $msg=&lock4tc ($from, $from_ty\
pe, \"LREAD\", \"\");\n    &lock4tc ($from, $from_\
type,\"LRELEASE\", $msg);\n    &lock4tc ($to, $to_\
type, $action, $msg);\n    return;\n  }\nsub isshe\
llpid\n  {\n    my $p=shift;\n    if (!lock4tc ($p\
, \"LLOCK\", \"LCHECK\")){return 0;}\n    else\n  \
    {\n	my $c=lock4tc($p, \"LLOCK\", \"LREAD\");\n\
	if ( $c=~/-SHELL-/){return 1;}\n      }\n    retu\
rn 0;\n  }\nsub isrootpid\n  {\n    if(lock4tc (ge\
tppid(), \"LLOCK\", \"LCHECK\")){return 0;}\n    e\
lse {return 1;}\n  }\nsub lock4tc\n	{\n	  my ($pid\
,$type,$action,$value)=@_;\n	  my $fname;\n	  my $\
host=hostname;\n	  \n	  if ($type eq \"LLOCK\"){$f\
name=\"$LOCKDIR/.$pid.$host.lock4tcoffee\";}\n	  e\
lsif ( $type eq \"LERROR\"){ $fname=\"$LOCKDIR/.$p\
id.$host.error4tcoffee\";}\n	  elsif ( $type eq \"\
LWARNING\"){ $fname=\"$LOCKDIR/.$pid.$host.warning\
4tcoffee\";}\n	  \n	  if ($debug_lock)\n	    {\n	 \
     print STDERR \"\\n\\t---lock4tc(tcg): $action\
 => $fname =>$value (RD: $LOCKDIR)\\n\";\n	    }\n\
\n	  if    ($action eq \"LCHECK\") {return -e $fna\
me;}\n	  elsif ($action eq \"LREAD\"){return file2\
string($fname);}\n	  elsif ($action eq \"LSET\") {\
return string2file ($value, $fname, \">>\");}\n	  \
elsif ($action eq \"LRESET\") {return string2file \
($value, $fname, \">\");}\n	  elsif ($action eq \"\
LRELEASE\") \n	    {\n	      if ( $debug_lock)\n		\
{\n		  my $g=new FileHandle;\n		  open ($g, \">>$f\
name\");\n		  print $g \"\\nDestroyed by $$\\n\";\\
n		  close ($g);\n		  safe_system (\"mv $fname $fn\
ame.old\");\n		}\n	      else\n		{\n		  unlink ($f\
name);\n		}\n	    }\n	  return \"\";\n	}\n	\nsub f\
ile2string\n	{\n	  my $file=@_[0];\n	  my $f=new F\
ileHandle;\n	  my $r;\n	  open ($f, \"$file\");\n	\
  while (<$f>){$r.=$_;}\n	  close ($f);\n	  return\
 $r;\n	}\nsub string2file \n    {\n    my ($s,$fil\
e,$mode)=@_;\n    my $f=new FileHandle;\n    \n   \
 open ($f, \"$mode$file\");\n    print $f  \"$s\";\
\n    close ($f);\n  }\n\nBEGIN\n    {\n      sran\
d;\n    \n      $SIG{'SIGUP'}='signal_cleanup';\n \
     $SIG{'SIGINT'}='signal_cleanup';\n      $SIG{\
'SIGQUIT'}='signal_cleanup';\n      $SIG{'SIGILL'}\
='signal_cleanup';\n      $SIG{'SIGTRAP'}='signal_\
cleanup';\n      $SIG{'SIGABRT'}='signal_cleanup';\
\n      $SIG{'SIGEMT'}='signal_cleanup';\n      $S\
IG{'SIGFPE'}='signal_cleanup';\n      \n      $SIG\
{'SIGKILL'}='signal_cleanup';\n      $SIG{'SIGPIPE\
'}='signal_cleanup';\n      $SIG{'SIGSTOP'}='signa\
l_cleanup';\n      $SIG{'SIGTTIN'}='signal_cleanup\
';\n      $SIG{'SIGXFSZ'}='signal_cleanup';\n     \
 $SIG{'SIGINFO'}='signal_cleanup';\n      \n      \
$SIG{'SIGBUS'}='signal_cleanup';\n      $SIG{'SIGA\
LRM'}='signal_cleanup';\n      $SIG{'SIGTSTP'}='si\
gnal_cleanup';\n      $SIG{'SIGTTOU'}='signal_clea\
nup';\n      $SIG{'SIGVTALRM'}='signal_cleanup';\n\
      $SIG{'SIGUSR1'}='signal_cleanup';\n\n\n     \
 $SIG{'SIGSEGV'}='signal_cleanup';\n      $SIG{'SI\
GTERM'}='signal_cleanup';\n      $SIG{'SIGCONT'}='\
signal_cleanup';\n      $SIG{'SIGIO'}='signal_clea\
nup';\n      $SIG{'SIGPROF'}='signal_cleanup';\n  \
    $SIG{'SIGUSR2'}='signal_cleanup';\n\n      $SI\
G{'SIGSYS'}='signal_cleanup';\n      $SIG{'SIGURG'\
}='signal_cleanup';\n      $SIG{'SIGCHLD'}='signal\
_cleanup';\n      $SIG{'SIGXCPU'}='signal_cleanup'\
;\n      $SIG{'SIGWINCH'}='signal_cleanup';\n     \
 \n      $SIG{'INT'}='signal_cleanup';\n      $SIG\
{'TERM'}='signal_cleanup';\n      $SIG{'KILL'}='si\
gnal_cleanup';\n      $SIG{'QUIT'}='signal_cleanup\
';\n      \n      our $debug_lock=$ENV{\"DEBUG_LOC\
K\"};\n      \n      \n      \n      \n      forea\
ch my $a (@ARGV){$CL.=\" $a\";}\n      if ( $debug\
_lock ){print STDERR \"\\n\\n\\n********** START P\
G: $PROGRAM *************\\n\";}\n      if ( $debu\
g_lock ){print STDERR \"\\n\\n\\n**********(tcg) L\
OCKDIR: $LOCKDIR $$ *************\\n\";}\n      if\
 ( $debug_lock ){print STDERR \"\\n --- $$ -- $CL\\
\n\";}\n      \n	     \n      \n      \n    }\nsub\
 flush_error\n  {\n    my $msg=shift;\n    return \
add_error ($EXIT_FAILURE,$$, $$,getppid(), $msg, $\
CL);\n  }\nsub add_error \n  {\n    my $code=shift\
;\n    my $rpid=shift;\n    my $pid=shift;\n    my\
 $ppid=shift;\n    my $type=shift;\n    my $com=sh\
ift;\n    \n    $ERROR_DONE=1;\n    lock4tc ($rpid\
, \"LERROR\",\"LSET\",\"$pid -- ERROR: $type\\n\")\
;\n    lock4tc ($$, \"LERROR\",\"LSET\", \"$pid --\
 COM: $com\\n\");\n    lock4tc ($$, \"LERROR\",\"L\
SET\", \"$pid -- STACK: $ppid -> $pid\\n\");\n   \\
n    return $code;\n  }\nsub add_warning \n  {\n  \
  my $rpid=shift;\n    my $pid =shift;\n    my $co\
mmand=shift;\n    my $msg=\"$$ -- WARNING: $comman\
d\\n\";\n    print STDERR \"$msg\";\n    lock4tc (\
$$, \"LWARNING\", \"LSET\", $msg);\n  }\n\nsub sig\
nal_cleanup\n  {\n    print dtderr \"\\n**** $$ (t\
cg) was killed\\n\";\n    &cleanup;\n    exit ($EX\
IT_FAILURE);\n  }\nsub clean_dir\n  {\n    my $dir\
=@_[0];\n    if ( !-d $dir){return ;}\n    elsif (\
!($dir=~/tmp/)){return ;}#safety check 1\n    elsi\
f (($dir=~/\\*/)){return ;}#safety check 2\n    el\
se\n      {\n	`rm -rf $dir`;\n      }\n    return;\
\n  }\nsub cleanup\n  {\n    #print stderr \"\\n--\
--tc: $$ Kills $PIDCHILD\\n\";\n    #kill (SIGTERM\
,$PIDCHILD);\n    my $p=getppid();\n    $CLEAN_EXI\
T_STARTED=1;\n    \n    \n    \n    if (&lock4tc($\
$,\"LERROR\", \"LCHECK\", \"\"))\n      {\n	my $pp\
id=getppid();\n	if (!$ERROR_DONE) \n	  {\n	    &lo\
ck4tc($$,\"LERROR\", \"LSET\", \"$$ -- STACK: $p -\
> $$\\n\");\n	    &lock4tc($$,\"LERROR\", \"LSET\"\
, \"$$ -- COM: $CL\\n\");\n	  }\n      }\n    my $\
warning=&lock4tc($$, \"LWARNING\", \"LREAD\", \"\"\
);\n    my $error=&lock4tc($$,  \"LERROR\", \"LREA\
D\", \"\");\n    #release error and warning lock i\
f root\n    \n    if (isrootpid() && ($warning || \
$error) )\n      {\n	\n	print STDERR \"***********\
***** Summary *************\\n$error\\n$warning\\n\
\";\n\n	&lock4tc($$,\"LERROR\",\"RELEASE\",\"\");\\
n	&lock4tc($$,\"LWARNING\",\"RELEASE\",\"\");\n   \
   } \n    \n    \n    foreach my $f (@TMPFILE_LIS\
T)\n      {\n	if (-e $f){unlink ($f);} \n      }\n\
    foreach my $d (@TMPDIR_LIST)\n      {\n	clean_\
dir ($d);\n      }\n    #No More Lock Release\n   \
 #&lock4tc($$,\"LLOCK\",\"LRELEASE\",\"\"); #relea\
se lock \n\n    if ( $debug_lock ){print STDERR \"\
\\n\\n\\n********** END PG: $PROGRAM ($$) ********\
*****\\n\";}\n    if ( $debug_lock ){print STDERR \
\"\\n\\n\\n**********(tcg) LOCKDIR: $LOCKDIR $$ **\
***********\\n\";}\n  }\nEND \n  {\n    \n    &cle\
anup();\n  }\n   \n\nsub safe_system \n{\n  my $co\
m=shift;\n  my $ntry=shift;\n  my $ctry=shift;\n  \
my $pid;\n  my $status;\n  my $ppid=getppid();\n  \
if ($com eq \"\"){return 1;}\n  \n  \n\n  if (($pi\
d = fork ()) < 0){return (-1);}\n  if ($pid == 0)\\
n    {\n      set_lock($$, \" -SHELL- $com (tcg)\"\
);\n      exec ($com);\n    }\n  else\n    {\n    \
  lock4tc ($$, \"LLOCK\", \"LSET\", \"$pid\\n\");#\
update parent\n      $PIDCHILD=$pid;\n    }\n  if \
($debug_lock){printf STDERR \"\\n\\t .... safe_sys\
tem (fasta_seq2hmm)  p: $$ c: $pid COM: $com\\n\";\
}\n\n  waitpid ($pid,WTERMSIG);\n\n  shift_lock ($\
pid,$$, \"LWARNING\",\"LWARNING\", \"LSET\");\n\n \
 if ($? == $EXIT_FAILURE || lock4tc($pid, \"LERROR\
\", \"LCHECK\", \"\"))\n    {\n      if ($ntry && \
$ctry <$ntry)\n	{\n	  add_warning ($$,$$,\"$com fa\
iled [retry: $ctry]\");\n	  lock4tc ($pid, \"LRELE\
ASE\", \"LERROR\", \"\");\n	  return safe_system (\
$com, $ntry, ++$ctry);\n	}\n      elsif ($ntry == \
-1)\n	{\n	  if (!shift_lock ($pid, $$, \"LERROR\",\
 \"LWARNING\", \"LSET\"))\n	    {\n	      add_warn\
ing ($$,$$,\"$com failed\");\n	    }\n	  else\n	  \
  {\n	      lock4tc ($pid, \"LRELEASE\", \"LERROR\\
", \"\");\n	    }\n	  return $?;}\n      else\n	{\\
n	  if (!shift_lock ($pid,$$, \"LERROR\",\"LERROR\\
", \"LSET\"))\n	    {\n	      myexit(add_error ($E\
XIT_FAILURE,$$,$pid,getppid(), \"UNSPECIFIED syste\
m\", $com));\n	    }\n	}\n    }\n  return $?;\n}\n\
\nsub check_configuration \n    {\n      my @l=@_;\
\n      my $v;\n      foreach my $p (@l)\n	{\n	  \\
n	  if   ( $p eq \"EMAIL\")\n	    { \n	      if ( \
!($EMAIL=~/@/))\n		{\n		add_warning($$,$$,\"Could \
Not Use EMAIL\");\n		myexit(add_error ($EXIT_FAILU\
RE,$$,$$,getppid(),\"EMAIL\",\"$CL\"));\n	      }\\
n	    }\n	  elsif( $p eq \"INTERNET\")\n	    {\n	 \
     if ( !&check_internet_connection())\n		{\n		 \
 myexit(add_error ($EXIT_FAILURE,$$,$$,getppid(),\\
"INTERNET\",\"$CL\"));\n		}\n	    }\n	  elsif( $p \
eq \"wget\")\n	    {\n	      if (!&pg_is_installed\
 (\"wget\") && !&pg_is_installed (\"curl\"))\n		{\\
n		  myexit(add_error ($EXIT_FAILURE,$$,$$,getppid\
(),\"PG_NOT_INSTALLED:wget\",\"$CL\"));\n		}\n	   \
 }\n	  elsif( !(&pg_is_installed ($p)))\n	    {\n	\
      myexit(add_error ($EXIT_FAILURE,$$,$$,getppi\
d(),\"PG_NOT_INSTALLED:$p\",\"$CL\"));\n	    }\n	}\
\n      return 1;\n    }\nsub pg_is_installed\n  {\
\n    my @ml=@_;\n    my $r, $p, $m;\n    my $supp\
orted=0;\n    \n    my $p=shift (@ml);\n    if ($p\
=~/::/)\n      {\n	if (safe_system (\"perl -M$p -e\
 1\")==$EXIT_SUCCESS){return 1;}\n	else {return 0;\
}\n      }\n    else\n      {\n	$r=`which $p 2>/de\
v/null`;\n	if ($r eq \"\"){return 0;}\n	else {retu\
rn 1;}\n      }\n  }\n\n\n\nsub check_internet_con\
nection\n  {\n    my $internet;\n    my $tmp;\n   \
 &check_configuration ( \"wget\"); \n    \n    $tm\
p=&vtmpnam ();\n    \n    if     (&pg_is_installed\
    (\"wget\")){`wget www.google.com -O$tmp >/dev/\
null 2>/dev/null`;}\n    elsif  (&pg_is_installed \
   (\"curl\")){`curl www.google.com -o$tmp >/dev/n\
ull 2>/dev/null`;}\n    \n    if ( !-e $tmp || -s \
$tmp < 10){$internet=0;}\n    else {$internet=1;}\\
n    if (-e $tmp){unlink $tmp;}\n\n    return $int\
ernet;\n  }\nsub check_pg_is_installed\n  {\n    m\
y @ml=@_;\n    my $r=&pg_is_installed (@ml);\n    \
if (!$r && $p=~/::/)\n      {\n	print STDERR \"\\n\
You Must Install the perl package $p on your syste\
m.\\nRUN:\\n\\tsudo perl -MCPAN -e 'install $pg'\\\
n\";\n      }\n    elsif (!$r)\n      {\n	myexit(f\
lush_error(\"\\nProgram $p Supported but Not Insta\
lled on your system\"));\n      }\n    else\n     \
 {\n	return 1;\n      }\n  }\n\n\n\n","\n\n\n\n\nm\
y $FMODEL =\"\"; \nmy $TMPDIR = \"/tmp\";\n\n\n\n\\
nmy $NUCALPH = \"ACGTUNRYMKSWHBVD\";\nmy $PRIMNUCA\
LPH = \"ACGTUN\";\nuse vars qw($NUCALPH $PRIMNUCAL\
PH $TMPDIR);\n\n\nmy $errmsg;\nuse vars qw($errmsg\
);\n\n\n\nuse Getopt::Long;\nuse Cwd;\nuse File::B\
asename;\nuse File::Temp qw/ tempfile tempdir /;\n\
use File::Copy;\nuse File::Path;\n\n\n\nsub usage(\
;$)\n{\n    my ($errmsg) = @_;\n    my $myname = b\
asename($0);\n\n    if ($errmsg) {\n        print \
STDERR \"ERROR: $errmsg\\n\";\n    }\n\n    print \
STDERR << \"EOF\";\n    \n$myname: align two seque\
nces by means of consan\\'s sfold\nUsage:\n $mynam\
e -i file -o file -d path\nOptions:\n -i|--in : pa\
irwise input sequence file\n -o|--out: output alig\
nment\n -d|--directory containing data\n\nEOF\n}\n\
\nsub read_stk_aln \n  {\n    my $f=$_[0];\n    my\
 ($seq, $id);\n    \n    my %hseq;\n\n    open (ST\
K, \"$f\");\n    while (<STK>)\n      {\n	if ( /^#\
/ || /^\\/\\// || /^\\s*$/){;}\n	else\n	  {\n	    \
($id,$seq)=/(\\S+)\\s+(\\S+)/;\n	    $hseq{$id}{'s\
eq'}.=$seq;\n	  }\n      }\n    close (STK);\n    \
return %hseq;\n  }\nsub read_fasta_seq \n  {\n    \
my $f=$_[0];\n    my %hseq;\n    my (@seq, @com, @\
name);\n    my ($a, $s,$nseq);\n\n    open (F, $f)\
;\n    while (<F>)\n      {\n	$s.=$_;\n      }\n  \
  close (F);\n\n    \n    @name=($s=~/>(.*).*\\n[^\
>]*/g);\n    \n    @seq =($s=~/>.*.*\\n([^>]*)/g);\
\n    @com =($s=~/>.*(.*)\\n([^>]*)/g);\n\n    \n \
   $nseq=$#name+1;\n    \n    for ($a=0; $a<$nseq;\
 $a++)\n      {\n	my $n=$name[$a];\n	$hseq{$n}{nam\
e}=$n;\n	$hseq{$n}{seq}=$seq[$a];\n	$hseq{$n}{com}\
=$com[$a];\n      }\n    return %hseq;\n  }\n\n\n\\
nsub sfold_parseoutput($$)\n{\n    my ($frawout, $\
foutfa) = @_;\n    my %haln;\n    my ($fstk, $cmd,\
 $id);\n    open FOUTFA, \">$foutfa\";\n    \n    \
$fstk = $frawout . \".stk\";\n    \n    # first li\
ne of raw out contains info\n    # remaining stuff\
 is stockholm formatted\n    $cmd = \"sed -e '1d' \
$frawout\";\n    system(\"$cmd > $fstk\");\n    if\
 ($? != 0) {\n        $errmsg = \"command failed w\
ith exit status $?.\";\n        $errmsg .=  \"Comm\
and was \\\"$cmd\\\"\";\n        return -1;\n    }\
\n\n    # this gives an error message. just ignore\
 it...\n    %haln=read_stk_aln ( $fstk);\n    fore\
ach $i (keys (%haln))\n      {\n	my $s;\n	$s=$haln\
{$i}{'seq'};\n	$s =~ s/\\./-/g;\n	print FOUTFA \">\
$i\\n$s\\n\";\n      }\n    close FOUTFA;\n    ret\
urn 0;\n}\n\n\n\n\nsub sfold_wrapper($$$$)\n{\n   \
 \n    my ($fs1, $fs2, $fmodel, $foutfa) = @_;\n  \
  \n\n    my ($cmd, $frawout, $ferrlog, $freadme, \
$ftimelog, $fstk);\n\n    # add  basename($fmsqin)\
 (unknown here!)\n    $frawout = \"sfold.log\";\n \
   $ferrlog = \"sfold.err\";\n    $ftimelog = \"sf\
old.time\";\n    $freadme =  \"sfold.README\";\n  \
  $fstk = \"sfold.stk\";\n    \n    # prepare exec\
ution...\n    #\n    # ./tmp is essential for dswp\
align\n    # otherwise you'll get a segfault\n    \
mkdir \"./tmp\";\n    \n    $cmd = \"sfold -m $fmo\
del $fs1 $fs2\";\n    open(FREADME,\">$freadme\");\
\n    print FREADME \"$cmd\\n\"; \n    close(FREAD\
ME);\n\n    # and go\n    #\n    system(\"/usr/bin\
/time -p -o $ftimelog $cmd >$frawout 2>$ferrlog\")\
;\n    if ($? != 0) {\n        $errmsg = \"command\
 failed with exit status $?\";\n        $errmsg .=\
 \"command was \\\"$cmd\\\". See \" . getcwd . \"\\
\n\";\n        return -1;\n    }\n\n    return sfo\
ld_parseoutput($frawout, $foutfa);\n}\n\n\n\n\n\n\\
n\nmy ($help, $fmsqin, $fmsaout);\nGetOptions(\"he\
lp\"  => \\$help,\n           \"in=s\" => \\$fmsqi\
n,\n           \"out=s\" => \\$fmsaout,\n	   \"dat\
a=s\" => \\$ref_dir);\n\n\n\nif ($help) {\n    usa\
ge();\n    exit(0);\n}\nif (! defined($fmsqin)) {\\
n    usage('missing input filename');\n    exit(1)\
;\n}\nif (! defined($fmsaout)) {\n    usage('missi\
ng output filename');\n    exit(1);\n\n}\nif (scal\
ar(@ARGV)) {\n    usage('Unknown remaining args');\
\n    exit(1);\n}\n\n$FMODEL = \"$ref_dir/mix80.mo\
d\";\nif (! -e \"$FMODEL\") {\n    die(\"couldn't \
find sfold grammar model file. Expected $FMODEL\\n\
\");\n}\n\n\nmy %hseq=read_fasta_seq ($fmsqin);\nm\
y $id;\n\nforeach $id (keys(%hseq))\n  {\n    push\
(@seq_array, $hseq{$id});\n  }\n\nif ( scalar(@seq\
_array) != 2 ) {\n    die(\"Need *exactly* two seq\
uences as input (pairwise alignment!).\")\n}\n\n\n\
\nmy ($sec, $min, $hour, $mday, $mon, $year, $wday\
, $yday, $isdst) = localtime(time);\nmy $datei = s\
printf(\"%4d-%02d-%02d\", $year+1900, $mon+1, $mda\
y);\nmy $templ = basename($0) . \".\" . $datei . \\
".pid-\" . $$ . \".XXXXXX\";\nmy $wd = tempdir ( $\
templ, DIR => $TMPDIR);\n\ncopy($fmsqin, \"$wd/\" \
. basename($fmsqin) . \".org\"); # for reproductio\
n\ncopy($FMODEL, \"$wd\");\nmy $fmodel = basename(\
$FMODEL);\nmy $orgwd = getcwd;\nchdir $wd;\n\n\n\n\
my @sepseqfiles;\nforeach $id (keys(%hseq)) {\n   \
 my ($seq, $orgseq, $fname, $sout);\n    $seq=$hse\
q{$id}{'seq'};\n    \n    $fname = basename($fmsqi\
n) . \"_$id.fa\";\n    # replace funnies in file/i\
d name (e.g. \"/\" \" \" etc)\n    $fname =~ s,[/ \
],_,g;\n    open (PF, \">$fname\");\n    print (PF\
 \">$id\\n$seq\\n\");\n    close (PF);\n\n    push\
(@sepseqfiles, $fname);\n}\n\nmy ($f1, $f2, $fout)\
;\n$f1 = $sepseqfiles[0];\n$f2 = $sepseqfiles[1];\\
n$fout = $wd . basename($fmsqin) . \".out.fa\";\ni\
f (sfold_wrapper($f1, $f2, $fmodel, \"$fout\") != \
0) {\n    printf STDERR \"ERROR: See logs in $wd\\\
n\";\n    exit(1);\n} else {\n    chdir $orgwd;\n \
   copy($fout, $fmsaout);\n    rmtree($wd);\n   ex\
it(0);\n}\n","\nuse Env qw(HOST);\nuse Env qw(HOME\
);\nuse Env qw(USER);\n\n\n$tmp=clean_cr ($ARGV[0]\
);\nopen (F, $tmp);\n\nwhile ( <F>)\n  {\n    my $\
l=$_;\n    if ( $l=~/^# STOCKHOLM/){$stockholm=1;}\
\n    elsif ( $stockholm && $l=~/^#/)\n      {\n	$\
l=~/^#(\\S+)\\s+(\\S+)\\s+(\\S*)/g;\n	$l=\"_stockh\
olmhasch_$1\\_stockholmspace_$2 $3\\n\";\n      }\\
n    $file.=$l;\n  }\nclose (F);\nunlink($tmp);\n$\
file1=$file;\n\n$file=~s/\\#/_hash_symbol_/g;\n$fi\
le=~s/\\@/_arobase_symbol_/g;\n\n\n$file=~s/\\n[\\\
.:*\\s]+\\n/\\n\\n/g;\n\n$file=~s/\\n[ \\t\\r\\f]+\
(\\b)/\\n\\1/g;\n\n\n$file=~s/(\\n\\S+)(\\s+)(\\S)\
/\\1_blank_\\3/g;\n\n$file=~s/[ ]//g;\n$file=~s/_b\
lank_/ /g;\n\n\n\n$file =~s/\\n\\s*\\n/#/g;\n\n$fi\
le.=\"#\";\n$file =~s/\\n/@/g;\n\n\n\n\n@blocks=sp\
lit /\\#/, $file;\nshift (@blocks);\n@s=split /\\@\
/, $blocks[0];\n$nseq=$#s+1;\n\n\n\n$file=join '@'\
, @blocks;\n@lines=split /\\@/,$file;\n\n$c=0;\n\n\
foreach $l (@lines)\n  {\n    if (!($l=~/\\S/)){ne\
xt;}\n    elsif ($stockholm && ($l=~/^\\/\\// || $\
l=~/STOCKHOLM/)){next;}#get read of STOCHOLM Termi\
nator\n   \n    $l=~/(\\S+)\\s+(\\S*)/g;\n    $n=$\
1; $s=$2;\n    \n    $seq[$c].=$s;\n    $name[$c]=\
$n;\n    $c++;\n    \n    if ( $c==$nseq){$c=0;}\n\
    \n  } \n\nif ( $c!=0)\n      {\n	print STDERR \
\"ERROR: $ARGV[0] is NOT an MSA in Clustalw format\
: make sure there is no blank line within a block \
[ERROR]\\n\";\n	exit (EXIT_FAILURE);\n      }\n\nf\
or ($a=0; $a< $nseq; $a++)\n  {\n    $name[$a]=cle\
anstring ($name[$a]);\n    $seq[$a]=cleanstring ($\
seq[$a]);\n    $seq[$a]=breakstring($seq[$a], 60);\
\n    \n    $line=\">$name[$a]\\n$seq[$a]\\n\";\n \
   \n    print \"$line\";\n  }\nexit (EXIT_SUCCESS\
);\n\nsub cleanstring\n  {\n    my $s=@_[0];\n    \
$s=~s/_hash_symbol_/\\#/g;\n    $s=~s/_arobase_sym\
bol_/\\@/g;\n    $s=~s/[ \\t]//g;\n    return $s;\\
n  }\nsub breakstring\n  {\n    my $s=@_[0];\n    \
my $size=@_[1];\n    my @list;\n    my $n,$ns, $sy\
mbol;\n    \n    @list=split //,$s;\n    $n=0;$ns=\
\"\";\n    foreach $symbol (@list)\n      {\n	if (\
 $n==$size)\n	  {\n	    $ns.=\"\\n\";\n	    $n=0;\\
n	  }\n	$ns.=$symbol;\n	$n++;\n      }\n    return\
 $ns;\n    }\n\nsub clean_cr\n  {\n    my $f=@_[0]\
;\n    my $file;\n    \n    $tmp=\"f$.$$\";\n    \\
n    \n    open (IN, $f);\n    open (OUT, \">$tmp\\
");\n    \n    while ( <IN>)\n      {\n	$file=$_;\\
n	$file=~s/\\r\\n/\\n/g;\n	$file=~s/\\n\\r/\\n/g;\\
n	$file=~s/\\r\\r/\\n/g;\n	$file=~s/\\r/\\n/g;\n	p\
rint OUT \"$file\";\n      }\n    \n    close (IN)\
;\n    close (OUT);\n    return $tmp;\n  }\n","use\
 Env qw(HOST);\nuse Env qw(HOME);\nuse Env qw(USER\
);\n\n\n$query_start=-1;\n$query_end=-1;\n\nwhile \
(<>)\n  {\n    if ( /\\/\\//){$in_aln=1;}\n    els\
if ( $in_aln && /(\\S+)\\s+(.*)/)\n      {\n\n\n	$\
name=$1;\n	\n\n	$seq=$2;\n	$seq=~s/\\s//g;\n      \
  $seq=~s/\\~/\\-/g;\n	$seq=~s/\\./\\-/g;\n	if ( $\
list{$n}{'name'} && $list{$n}{'name'} ne $name)\n	\
  {\n	    print \"$list{$n}{'name'} Vs $name\";\n	\
    \n	    exit (EXIT_FAILURE);\n	  }\n	else\n	  {\
\n	    $list{$n}{'name'}= $name;\n	  }\n\n	$list{$\
n}{'seq'}=$list{$n}{'seq'}.$seq;\n	\n	$nseq=++$n;\\
n	\n      }\n    else\n      {$n=0;}\n  }\n\n\nfor\
 ($a=0; $a<$nseq; $a++)\n  {\n    print \">$list{$\
a}{'name'}\\n$list{$a}{'seq'}\\n\";\n  }\n      \n\
","\nuse Env qw(HOST);\nuse Env qw(HOME);\nuse Env\
 qw(USER);\n\n                                    \
                    \nuse strict;                 \
                            \nuse warnings;\nuse d\
iagnostics;\n\nmy $in_hit_list, my $in_aln=0, my(%\
name_list)=(),my (%list)=(),my $n_seq=0; my $test=\
0;\nmy($j)=0, my $n=0, my $nom, my $lg_query, my %\
vu=();\n\nopen (F, \">tmp\");\n\n$/=\"\\n\";\nwhil\
e (<>)\n{\n    print F $_;\n    if($_ =~ /Query=\\\
s*(.+?)\\s/i) { $nom=$1;}\n\n    if ( /Sequences p\
roducing significant alignments/){$in_hit_list=1;}\
\n    \n    if ($_=~ /^pdb\\|/i) { $_=~ s/pdb\\|//\
g; }\n    if ($_=~ /^(1_\\d+)\\s+\\d+/) { $_=~ s/$\
1/QUERY/;}\n      \n    if ( /^(\\S+).+?\\s+[\\d.]\
+\\s+([\\de.-]+)\\s+$/ && $in_hit_list)	\n    {\n	\
my($id)=$1; # \n	$id=~ s/\\|/_/g; #\n	if ($id =~ /\
.+_$/) { chop($id) }; #\n	$name_list{$n_seq++}=$id\
;\n	$name_list{$n_seq-1}=~ s/.*\\|//g;     \n    }\
\n  \n    if (/query/i) {$in_aln=1;}\n    if ( /^(\
\\S+)\\s+(\\d+)\\s+([a-zA-Z-]+)\\s+(\\d+)/ || /^(\\
\S+)(\\s+)(\\-+)(\\s+)/ && ($in_aln == 1))\n    {\\
n	my $name=$1;\n	my $start=$2;\n	my $seq=$3;\n	my \
$end=$4;\n		\n	if ($name =~ /QUERY/i) { $lg_query=\
length($seq); }\n\n	unless ($test > $n) #m\n	{\n	 \
   my(@seqq)= split('',$seq);\n	    my($gap_missin\
g)= scalar(@seqq);\n	    \n	    while ($gap_missin\
g != $lg_query)  { unshift (@seqq,\"-\"); $gap_mis\
sing= scalar(@seqq); }\n	    $seq=join('',@seqq); \
 #m\n	}\n	\n	if ($name =~ /QUERY/i)\n	{\n	    $n=0\
; %vu=(); $j=0;\n	    $list{$n}{'real_name'}=\"$no\
m\";\n	}	\n	else\n	{\n	    unless (exists $vu{$nam\
e}) { ++$j;}	\n	    $list{$n}{'real_name'}=$name_l\
ist{$j-1};\n	}\n		\n	$list{$n}{'name'}=$name;\n\n	\
$seq=~tr/a-z/A-Z/;\n	$list{$n}{'seq'}=$list{$n}{'s\
eq'};\n	$list{$n}{'seq'}.=$seq;\n\n	$n++;\n	$vu{$n\
ame}++;\n	$test++;\n   } \n    \n}\n\nmy @numero=(\
);\n\nfor (my $a=0; $a<$n; $a++) #m\n{\n    my $lo\
ng=length($list{0}{'seq'});  \n    my $long1= leng\
th($list{$a}{'seq'});\n  \n    while ($long1 ne $l\
ong)\n    {\n	$list{$a}{'seq'}.=\"-\";\n	$long1= l\
ength ($list{$a}{'seq'});\n    } \n \n    push (@n\
umero,\"$list{$a}{'name'} $list{$a}{'real_name'}\\\
n\");\n}\n\nmy %dejavu=();\n\n\nfor (my $i=0; $i<=\
$#numero; $i++)\n{\n    my $s=\">$list{$i}{'real_n\
ame'}\\n$list{$i}{'seq'}\\n\";\n    my $k=0;\n    \
\n    if (exists $dejavu{$numero[$i]}) {next;}\n  \
  else\n    {	\n	for ($j=0; $j<$n ; $j++)\n	{\n	  \
  if (\"$numero[$i]\" eq \"$numero[$j]\" && $j != \
$i )\n	    {\n		++$k;\n		$s .=\">$list{$j}{'real_n\
ame'}\\n$list{$j}{'seq'}\\n\";\n	    }\n	}	\n    }\
\n    \n    if ($k>0) \n    {\n	my $cons;\n	open (\
SOR,\">tempo_aln2cons\"); print SOR $s;  close SOR\
 ;\n	open (COM,\"t_coffee -other_pg seq_reformat -\
in tempo_aln2cons -action +aln2cons +upper |\") ; \
\n     	while (<COM>)\n	{	\n	    if (/^>/) { $cons\
 =\">$list{$i}{'real_name'}\\n\"; next;}\n	    $_=\
~ s/\\n//g;\n	    $cons .=$_;\n	}\n	close COM; unl\
ink (\"tempo_aln2cons\");\n	print $cons,\"\\n\"; p\
rint F $cons,\"\\n\";\n    }	\n    else  { print $\
s;  print F $s; }\n    \n    $dejavu{$numero[$i]}+\
+;\n} #m\n\nexit;\n\n\n\n\n\n\n\n\n\n\n\n","use En\
v;\n\n\n$tmp_dir=\"\";\n$init_dir=\"\";\n$program=\
\"tc_generic_method.pl\";\n\n$blast=@ARGV[0];\n\n$\
name=\"query\";$seq=\"\";\n%p=blast_xml2profile($n\
ame,$seq,100, 0, 0, $blast);\n&output_profile (%p)\
;\n\n\nsub output_profile\n  {\n    my (%profile)=\
(@_);\n    my ($a);\n    for ($a=0; $a<$profile{n}\
; $a++)\n      {\n	\n	print \">$profile{$a}{name} \
$profile{$a}{comment}\\n$profile{$a}{seq}\\n\";\n \
     }\n    return;\n  }\nsub file_contains \n  {\\
n    my ($file, $tag, $max)=(@_);\n    my ($n);\n \
   $n=0;\n    \n    if ( !-e $file && ($file =~/$t\
ag/)) {return 1;}\n    elsif ( !-e $file){return 0\
;}\n    else \n      {\n	open (FC, \"$file\");\n	w\
hile ( <FC>)\n	  {\n	    if ( ($_=~/$tag/))\n	    \
  {\n		close (FC);\n		return 1;\n	      }\n	    el\
sif ($max && $n>$max)\n	      {\n		close (FC);\n		\
return 0;\n	      }\n	    $n++;\n	  }\n      }\n  \
  close (FC);\n    return 0;\n  }\n	    \n	  \nsub\
 file2string\n  {\n    my $f=@_[0];\n    my $strin\
g, $l;\n    open (F,\"$f\");\n    while (<F>)\n   \
   {\n\n	$l=$_;\n	#chomp ($l);\n	$string.=$l;\n   \
   }\n    close (F);\n    $string=~s/\\r\\n//g;\n \
   $string=~s/\\n//g;\n    return $string;\n  }\n\\
n\n\nsub tag2value \n  {\n    \n    my $tag=(@_[0]\
);\n    my $word=(@_[1]);\n    my $return;\n    \n\
    $tag=~/$word=\"([^\"]+)\"/;\n    $return=$1;\n\
    return $return;\n  }\n      \nsub hit_tag2pdbi\
d\n  {\n    my $tag=(@_[0]);\n    my $pdbid;\n    \
   \n    $tag=~/id=\"(\\S+)\"/;\n    $pdbid=$1;\n \
   $pdbid=~s/_//;\n    return $pdbid;\n  }\nsub id\
2pdbid \n  {\n    my $id=@_[0];\n  \n    if ($id =\
~/pdb/)\n      {\n	$id=~/pdb(.*)/;\n	$id=$1;\n    \
  }\n    $id=~s/[|�_]//g;\n    return $id;\n  }\ns\
ub set_blast_type \n  {\n    my $file =@_[0];\n   \
 if (&file_contains ($file,\"EBIApplicationResult\\
",100)){$BLAST_TYPE=\"EBI\";}\n    elsif (&file_co\
ntains ($file,\"NCBI_BlastOutput\",100)) {$BLAST_T\
YPE=\"NCBI\";}\n    else\n      {\n	$BLAST_TYPE=\"\
\";\n      }\n    return $BLAST_TYPE;\n  }\nsub bl\
ast_xml2profile \n  {\n    my ($name,$seq,$maxid, \
$minid, $mincov, $file)=(@_);\n    my (%p, $a, $st\
ring, $n);\n    \n\n\n    if ($BLAST_TYPE eq \"EBI\
\" || &file_contains ($file,\"EBIApplicationResult\
\",100)){%p=ebi_blast_xml2profile(@_);}\n    elsif\
 ($BLAST_TYPE eq \"NCBI\" || &file_contains ($file\
,\"NCBI_BlastOutput\",100)){%p=ncbi_blast_xml2prof\
ile(@_);}\n    else \n      {\n	print \"**********\
** ERROR: Blast Returned an unknown XML Format ***\
*******************\";\n	die;\n      }\n    for ($\
a=0; $a<$p{n}; $a++)\n      {\n	my $name=$p{$a}{na\
me};\n	$p{$name}{seq}=$p{$a}{seq};\n      }\n    r\
eturn %p;\n  }\nsub ncbi_blast_xml2profile \n  {\n\
    my ($name,$seq,$maxid, $minid, $mincov, $strin\
g)=(@_);\n    my ($L,$l, $a,$b,$c,$d,$nhits,@ident\
ifyerL);\n    \n    \n    $seq=~s/[^a-zA-Z]//g;\n \
   $L=length ($seq);\n    \n    %hit=&xml2tag_list\
 ($string, \"Hit\");\n    \n    \n    for ($nhits=\
0,$a=0; $a<$hit{n}; $a++)\n      {\n	my ($ldb,$id,\
 $identity, $expectation, $start, $end, $coverage,\
 $r);\n	my (%ID,%DE,%HSP);\n	\n	$ldb=\"\";\n\n	%ID\
=&xml2tag_list ($hit{$a}{body}, \"Hit_id\");\n	$id\
entifyer=$ID{0}{body};\n	\n	%DE=&xml2tag_list ($hi\
t{$a}{body}, \"Hit_def\");\n	$definition=$DE{0}{bo\
dy};\n	\n	%HSP=&xml2tag_list ($hit{$a}{body}, \"Hs\
p\");\n	for ($b=0; $b<$HSP{n}; $b++)\n	  {\n	    m\
y (%START,%END,%E,%I,%Q,%M);\n\n	 \n	    %START=&x\
ml2tag_list ($HSP{$b}{body}, \"Hsp_query-from\");\\
n	    %HSTART=&xml2tag_list ($HSP{$b}{body}, \"Hsp\
_hit-from\");\n	    \n	    %LEN=  &xml2tag_list ($\
HSP{$b}{body}, \"Hsp_align-len\");\n	    %END=  &x\
ml2tag_list ($HSP{$b}{body}, \"Hsp_query-to\");\n	\
    %HEND=  &xml2tag_list ($HSP{$b}{body}, \"Hsp_h\
it-to\");\n	    %E=&xml2tag_list     ($HSP{$b}{bod\
y}, \"Hsp_evalue\");\n	    %I=&xml2tag_list     ($\
HSP{$b}{body}, \"Hsp_identity\");\n	    %Q=&xml2ta\
g_list     ($HSP{$b}{body}, \"Hsp_qseq\");\n	    %\
M=&xml2tag_list     ($HSP{$b}{body}, \"Hsp_hseq\")\
;\n	    \n	    for ($e=0; $e<$Q{n}; $e++)\n\n	    \
  {\n		$qs=$Q{$e}{body};\n		$ms=$M{$e}{body};\n		i\
f ($seq eq\"\"){$seq=$qs;$L=length($seq);}\n		\n		\
$expectation=$E{$e}{body};\n		$identity=($LEN{$e}{\
body}==0)?0:$I{$e}{body}/$LEN{$e}{body}*100;\n		$s\
tart=$START{$e}{body};\n		$end=$END{$e}{body};\n		\
$Hstart=$HSTART{$e}{body};\n		$Hend=$HEND{$e}{body\
};\n	\n		$coverage=(($end-$start)*100)/$L;\n\n	\n	\
	if ($identity>$maxid || $identity<$minid || $cove\
rage<$mincov){next;}\n		@lr1=(split (//,$qs));\n		\
@lr2=(split (//,$ms));\n		$l=$#lr1+1;\n		for ($c=0\
;$c<$L;$c++){$p[$nhits][$c]=\"-\";}\n		for ($d=0,$\
c=0; $c<$l; $c++)\n		  {\n		    $r=$lr1[$c];\n		  \
  if ( $r=~/[A-Za-z]/)\n		      {\n			\n			$p[$nhi\
ts][$d + $start-1]=$lr2[$c];\n			$d++;\n		      }\\
n		  }\n		$Qseq[$nhits]=$qs;\n		$Hseq[$nhits]=$ms;\
\n		$QstartL[$nhits]=$start;\n		$HstartL[$nhits]=$\
Hstart;\n		$identityL[$nhits]=$identity;\n		$endL[\
$nhits]=$end;\n		$definitionL[$nhits]=$definition;\
\n		$identifyerL[$nhits]=$identifyer;\n		$comment[\
$nhits]=\"$ldb|$identifyer [Eval=$expectation][id=\
$identity%][start=$Hstart end=$Hend]\";\n		$nhits+\
+;\n	      }\n	  }\n      }\n    \n    $profile{n}\
=0;\n    $profile{$profile{n}}{name}=$name;\n    $\
profile{$profile{n}}{seq}=$seq;\n    $profile {n}+\
+;\n    \n    for ($a=0; $a<$nhits; $a++)\n      {\
\n	$n=$a+1;\n	\n	$profile{$n}{name}=\"$name\\_$a\"\
;\n	$profile{$n}{seq}=\"\";\n	$profile{$n}{Qseq}=$\
Qseq[$a];\n	$profile{$n}{Hseq}=$Hseq[$a];\n	$profi\
le{$n}{Qstart}=$QstartL[$a];\n	$profile{$n}{Hstart\
}=$HstartL[$a];\n	$profile{$n}{identity}=$identity\
L[$a];\n	$profile{$n}{definition}=$definitionL[$a]\
;\n	$profile{$n}{identifyer}=$identifyerL[$a];\n	$\
profile{$n}{comment}=$comment[$a];\n	for ($b=0; $b\
<$L; $b++)\n	  {\n	    if ($p[$a][$b])\n	      {\n\
		$profile{$n}{seq}.=$p[$a][$b];\n	      }\n	    e\
lse\n	      {\n		$profile{$n}{seq}.=\"-\";\n	     \
 }\n	  }\n      }\n    \n    $profile{n}=$nhits+1;\
\n    return %profile;\n  }\nsub ebi_blast_xml2pro\
file \n  {\n    my ($name,$seq,$maxid, $minid, $mi\
ncov, $string)=(@_);\n    my ($L,$l, $a,$b,$c,$d,$\
nhits,@identifyerL,$identifyer);\n    \n\n    \n  \
  $seq=~s/[^a-zA-Z]//g;\n    $L=length ($seq);\n  \
  %hit=&xml2tag_list ($string, \"hit\");\n    \n  \
  for ($nhits=0,$a=0; $a<$hit{n}; $a++)\n      {\n\
	my ($ldb,$id, $identity, $expectation, $start, $e\
nd, $coverage, $r);\n	my (%Q,%M,%E,%I);\n	\n	$ldb=\
&tag2value ($hit{$a}{open}, \"database\");\n	$iden\
tifyer=&tag2value ($hit{$a}{open}, \"id\");\n\n	$d\
escription=&tag2value ($hit{$a}{open}, \"descripti\
on\");\n	\n	%Q=&xml2tag_list ($hit{$a}{body}, \"qu\
erySeq\");\n	%M=&xml2tag_list ($hit{$a}{body}, \"m\
atchSeq\");\n	%E=&xml2tag_list ($hit{$a}{body}, \"\
expectation\");\n	%I=&xml2tag_list ($hit{$a}{body}\
, \"identity\");\n	\n\n	for ($b=0; $b<$Q{n}; $b++)\
\n	  {\n	    \n	    \n	    $qs=$Q{$b}{body};\n	   \
 $ms=$M{$b}{body};\n	    if ($seq eq\"\"){$seq=$qs\
;$L=length($seq);}\n\n	    $expectation=$E{$b}{bod\
y};\n	    $identity=$I{$b}{body};\n	    \n	    	  \
  \n	    $start=&tag2value ($Q{$b}{open}, \"start\\
");\n	    $end=&tag2value ($Q{$b}{open}, \"end\");\
\n	    $startM=&tag2value ($M{$b}{open}, \"start\"\
);\n	    $endM=&tag2value ($M{$b}{open}, \"end\");\
\n	    $coverage=(($end-$start)*100)/$L;\n	    \n	\
   # print \"$id: ID: $identity COV: $coverage [$s\
tart $end]\\n\";\n	    \n	    \n	    if ($identity\
>$maxid || $identity<$minid || $coverage<$mincov){\
next;}\n	    # print \"KEEP\\n\";\n\n	    \n	    @\
lr1=(split (//,$qs));\n	    @lr2=(split (//,$ms));\
\n	    $l=$#lr1+1;\n	    for ($c=0;$c<$L;$c++){$p[\
$nhits][$c]=\"-\";}\n	    for ($d=0,$c=0; $c<$l; $\
c++)\n	      {\n		$r=$lr1[$c];\n		if ( $r=~/[A-Za-\
z]/)\n		  {\n		    \n		    $p[$nhits][$d + $start-\
1]=$lr2[$c];\n		    $d++;\n		  }\n	      }\n	  \n	\
    \n	    $identifyerL[$nhits]=$identifyer;\n	   \
 $comment[$nhits]=\"$ldb|$identifyer [Eval=$expect\
ation][id=$identity%][start=$startM end=$endM]\";\\
n	    $nhits++;\n	  }\n      }\n    \n    $profile\
{n}=0;\n    $profile{$profile{n}}{name}=$name;\n  \
  $profile{$profile{n}}{seq}=$seq;\n    $profile {\
n}++;\n    \n    for ($a=0; $a<$nhits; $a++)\n    \
  {\n	$n=$a+1;\n	$profile{$n}{name}=\"$name\\_$a\"\
;\n	$profile{$n}{seq}=\"\";\n	$profile{$n}{identif\
yer}=$identifyerL[$a];\n	\n	$profile{$n}{comment}=\
$comment[$a];\n	for ($b=0; $b<$L; $b++)\n	  {\n	  \
  if ($p[$a][$b])\n	      {\n		$profile{$n}{seq}.=\
$p[$a][$b];\n	      }\n	    else\n	      {\n		$pro\
file{$n}{seq}.=\"-\";\n	      }\n	  }\n      }\n  \
  $profile{n}=$nhits+1;\n    \n    return %profile\
;\n  }\n\nsub blast_xml2hit_list\n  {\n    my $str\
ing=(@_[0]);\n    return &xml2tag_list ($string, \\
"hit\");\n  }\nsub xml2tag_list  \n  {\n    my ($s\
tring_in,$tag)=@_;\n    my $tag_in, $tag_out;\n   \
 my %tag;\n    \n    if (-e $string_in)\n      {\n\
	$string=&file2string ($string_in);\n      }\n    \
else\n      {\n	$string=$string_in;\n      }\n    \
$tag_in1=\"<$tag \";\n    $tag_in2=\"<$tag>\";\n  \
  $tag_out=\"/$tag>\";\n    $string=~s/>/>##1/g;\n\
    $string=~s/</##2</g;\n    $string=~s/##1/<#/g;\
\n    $string=~s/##2/#>/g;\n    @l=($string=~/(\\<\
[^>]+\\>)/g);\n    $tag{n}=0;\n    $in=0;$n=-1;\n \
 \n \n\n    foreach $t (@l)\n      {\n\n	$t=~s/<#/\
/;\n	$t=~s/#>//;\n	\n	if ( $t=~/$tag_in1/ || $t=~/\
$tag_in2/)\n	  {\n	 \n	    $in=1;\n	    $tag{$tag{\
n}}{open}=$t;\n	    $n++;\n	    \n	  }\n	elsif ($t\
=~/$tag_out/)\n	  {\n	    \n\n	    $tag{$tag{n}}{c\
lose}=$t;\n	    $tag{n}++;\n	    $in=0;\n	  }\n	el\
sif ($in)\n	  {\n	   \n	    $tag{$tag{n}}{body}.=$\
t;\n	  }\n      }\n  \n    return %tag;\n  }\n\n\n\
\n\n","use Env qw(HOST);\nuse Env qw(HOME);\nuse E\
nv qw(USER);\nwhile (<>)\n  {\n    if ( /^>(\\S+)/\
)\n      {\n	if ($list{$1})\n	  {\n	    print \">$\
1_$list{$1}\\n\";\n	    $list{$1}++;\n	  }\n	else\\
n	  {\n	    print $_;\n	    $list{$1}=1;\n	  }\n  \
    }\n    else\n      {\n	print $_;\n      }\n  }\
\n      \n","\n\n\nuse Env qw(HOST);\nuse Env qw(H\
OME);\nuse Env qw(USER);\n\n\nopen (F,$ARGV[0]);\n\
while ( <>)\n  {\n    @x=/([^:,;\\)\\(\\s]+):[^:,;\
\\)\\(]*/g;\n    @list=(@list,@x);\n  }\n$n=$#list\
+1;\nforeach $n(@list){print \">$n\\nsequence\\n\"\
;}\n\n\nclose (F);\n","\nopen (F, $ARGV[0]);\n\nwh\
ile ( <F>)\n  {\n    @l=($_=~/(\\S+)/g);\n    \n  \
  $name=shift @l;\n    \n    print STDOUT \"\\n>$n\
ame\\n\";\n    foreach $e (@l){$e=($e eq \"0\")?\"\
O\":\"I\";print \"$e\";}\n  }\nclose (F);\n\n		   \
    \n    \n","use Env qw(HOST);\nuse Env qw(HOME)\
;\nuse Env qw(USER);\n\n$tmp=\"$ARGV[0].$$\";\nope\
n (IN, $ARGV[0]);\nopen (OUT, \">$tmp\");\n\nwhile\
 ( <IN>)\n  {\n    $file=$_;\n    $file=~s/\\r\\n/\
\\n/g;\n    $file=~s/\\n\\r/\\n/g;\n    $file=~s/\\
\r\\r/\\n/g;\n    $file=~s/\\r/\\n/g;\n    print O\
UT \"$file\";\n  }\nclose (IN);\nclose (OUT);\n\no\
pen (OUT, \">$ARGV[0]\");\nopen (IN, \"$tmp\");\n\\
nwhile ( <IN>)\n{\n  print OUT \"$_\";\n}\nclose (\
IN);\nclose (OUT);\nunlink ($tmp);\n\n"};
