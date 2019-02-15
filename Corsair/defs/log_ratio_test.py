#!/usr/bin/env python3

import Corsair as cor
from scipy.stats import chi2

def log_ratio_test(lv1, lv2, df):
    """
    Input: log-liklihood 1 and 2, degrees of freedom
    Returns: 2-delta, pvalue from chi2 test
    """
    twodelt = 2 * abs(lv1 - lv2)
    pvalue = chi2.sf(twodelt, df)

    return twodelt, pvalue
