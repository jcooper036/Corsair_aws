#!/usr/bin/env python3

def translate(sequence):
    """
    Input: nucleotide sequence
    Output: protein sequence translated from input
    """

    # codon table
    transtable = {
        'agg' : 'R',
        'aga' : 'R',
        'agc' : 'S',
        'agt' : 'S',
        'aag' : 'K',
        'aaa' : 'K',
        'aac' : 'N',
        'aat' : 'N',
        'aca' : 'T',
        'acc' : 'T',
        'acg' : 'T',
        'act' : 'T',
        'atg' : 'M',
        'ata' : 'I',
        'atc' : 'I',
        'att' : 'I',
        'cgg' : 'R',
        'cga' : 'R',
        'cgc' : 'R',
        'cgt' : 'R',
        'cag' : 'Q',
        'caa' : 'Q',
        'cac' : 'H',
        'cat' : 'H',
        'ccg' : 'P',
        'cca' : 'P',
        'ccc' : 'P',
        'cct' : 'P',
        'ctg' : 'L',
        'cta' : 'L',
        'ctc' : 'L',
        'ctt' : 'L',
        'tgg' : 'W',
        'tga' : 'X',
        'tgc' : 'C',
        'tgt' : 'C',
        'tag' : 'X',
        'taa' : 'X',
        'tac' : 'Y',
        'tat' : 'Y',
        'tcg' : 'S',
        'tca' : 'S',
        'tcc' : 'S',
        'tct' : 'S',
        'ttg' : 'L',
        'tta' : 'L',
        'ttc' : 'F',
        'ttt' : 'F',
        'ggg' : 'G',
        'gga' : 'G',
        'ggc' : 'G',
        'ggt' : 'G',
        'gag' : 'E',
        'gaa' : 'E',
        'gac' : 'D',
        'gat' : 'D',
        'gcg' : 'A',
        'gca' : 'A',
        'gcc' : 'A',
        'gct' : 'A',
        'gtg' : 'V',
        'gta' : 'V',
        'gtc' : 'V',
        'gtt' : 'V'}

    # this is a counting variable
    k = 3

    # this the blank string for the amino acid sequence
    aaseq = ''

    # stops when it gets to the end of the sequence=
    while k <= len(sequence):
        
        # try to add a codon. will reject because it won't find the key if the variable is blank
        try:
            aaseq += transtable[sequence[(k-3):k].lower()]
        except:
            aaseq += '' ## adds a blank space if no translation is possible
        
        # count up 3
        k = k + 3

    # return value is a string of amino acids
    return aaseq
