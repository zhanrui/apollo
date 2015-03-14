#!/usr/bin/env python
#-*-coding:utf-8-*- 
class ReportType:
    reportType={
                0:"datareport",
                1:"errorreport",
                2:"progressreport"}
    errReportResult={
                       0:"errordescrition"}
    progReportResult={
                      0:"currentcompletion",
                      1:"currentstatus"}  

scanType={"threatDocument":"木马检查",
           "fileRoutineCheck":"文件常规检查",
           "imageCheck":"图片检查"}   