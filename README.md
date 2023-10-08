# ScreenGuard : Hiding Sensitive information for Screen Sharing Applications

## Introduction

In screen sharing, a number of sensitive information can potentially be disclosed. This includes a
spectrum of personal data, including full names, addresses, financial details such as credit card
numbers and bank account details, authentication credentials like passwords and access tokens,
health-related information, legal documents, personal communications, proprietary business data,
educational records, and even location details. This sensitive information can come up in a
screen sharing session in mainly two forms. One category is textual data, such as emails or
content in editors handling documents like DOCs, PDFs, PowerPoint presentations, and
spreadsheets. Another category involves sensitive data embedded in images such as photos of
driver's licenses or other personal documents. The primary aim of this software is to mask any
sensitive information that users choose to block during screen sharing.

Since the main point of concern is textual information, if the text data can be inferred before it is
rendered as an image, processing overhead can be avoided. But a major limitation of this
approach is that not all textual information cannot be accessed before it is rendered, which is
explored in later sections. Due to the fact that sensitive information can come embedded in an
image, it is important to deploy image processing techniques. Unlike the text information access,
which is restricted to specific applications and dependent on the operating system, this image
processing approach will provide an end-to-end solution.

Text recognition is accomplished using tesseract, an open-source Optical Character Recognition
(OCR) engine. This engine is built on LSTM neural networks and comes pre-trained for over 100
languages and 35 scripts. However, for this project, only English language data is used for
recognition. The accuracy of the model has been improved by applying dynamic programming
alignment algorithms to identify text even when there is a reasonable amount of difference.
The software's performance bottleneck is tied to tesseract's recognition process. To overcome
this, a customized algorithm has been integrated. This algorithm tracks recognized text between
frames, effectively bypassing the bottleneck and resulting in smoother software performance
across frames.

## Text Recognition

Optical Character Recognition(OCR) is the process of converting images of typed, handwritten
or printed text into machine encoded text. It is an active field of research in pattern recognition
and artificial intelligence due to its important application. The tesseract OCR engine[12] is an
open source OCR engine which comes pre-trained for over 100 languages and 35 scripts. It is
built on Long Short-Term Memory (LSTM) neural networks, a type of recurrent neural network
architecture that is good at handling sequential data. The LSTM architecture enables it to capture
contextual dependencies within text, making it less susceptible to variations in font, size, and
style. This makes it well-suited for reading textual information from computer screens. While the
primary focus of Tesseract has been on scanned documents, its capabilities are well suited to
screen-captured text.

## Text Tracking

Another important topic explored in [8] is text tracking across multiple dynamic video frames.
As [9] explains, one way to match text from one frame to the next is by measuring how far the
recognized word in the current frame is from a possible word in the next frame. In situations like
screen captures, where text is often close together in following frames, this feature can be used to
improve accuracy. As explained in the previous chapter it is possible to track the text region by
tracking the position of the window where the text was first spotted. Text tracking can thus aid
the overall text recognition process.

## Text Matching

Text Matching is an additional step that has to be considered after text recognition in this
application’s context. The sensitive text can lie embedded within a sentence or with other
symbols, therefore this is an important step to reach the end to end functionality of this
application. In [10] the authors have explored a dynamic programming approach used to
calculate the similarity of DNA sequences, DNA sequences are basically a sequence of symbols.
Thus the same logic can be applied for text matching here as well.
The two sequences are considered identical if they contain no mismatches or gaps. By assigning
a penalty for each mismatch and each gap, the total sum of these penalties becomes a useful
measure for determining sequence similarity. The threshold penalty, a customizable parameter,
needs careful selection to prevent false positives. 

## Reference

[1] Kent, A., & Williams, J. G. (1996). Encyclopedia of Microcomputers: Volume 19 - Truth
Maintenance Systems to Visual Display Quality. CRC Press. Retrieved June 8, 2017, from ISBN
9780824727178.

[2] C. Tronche. "The Xlib Manual.". [Online]. Available:
https://tronche.com/gui/x/xlib/introduction/overview.html. [Accessed: Aug 15, 2023].

[3] A. Coopersmith, M. Dev, and the X.Org team (Eds.), "The X New Developer's Guide."
Edited by B. Massey, Portland, Oregon, USA, March 2012.

[4] The Qt Company. "Qt 6.5 All C++ Classes". [Online]. Available:
https://doc.qt.io/qt-6/classes.html. [Accessed: Aug 15, 2023].

[5] G. Schechter, "Under the hood of Desktop Window Manager," Greg Schechter's Blog,
MSDN Blogs. [Online]. Available:
https://blogs.msdn.microsoft.com/greg_schechter/2006/03/22/under-the-hood-of-desktop-windo
w-manager/. [Accessed: Aug 20, 2021].

[6] Apple. "Quartz." Available :https://developer.apple.com/documentation/quartz [Accessed:
Aug 20, 2021].

[7] Microsoft. "Windows API - Win32 apps." Available :
https://learn.microsoft.com/en-us/windows/win32/api/_winmsg/. [Accessed: Aug 20, 2021].

[8] X. Yin, Z. Zuo, S. Tian, and C. Liu, "Text Detection, Tracking and Recognition in Video: A
Comprehensive Survey," in IEEE Transactions on Image Processing, vol. 25, no. 6, pp.
2752-2773, June 2016, doi: 10.1109/TIP.2016.2551158.

[9] P. X. Nguyen, K. Wang, and S. Belongie, “Video text detection and recognition: Dataset and
benchmark,” in Proc. IEEE Winter Conf. Appl. Comput. Vis., Mar. 2014, pp. 776–783.

[10] J. Kleinberg and E. Tardos. Dynamic Programming. In Algorithm Design,(Eds 1), Cornell
University, pp 278-290.

[11]. Qianping, G. (2023, August 10). "Dynamic Programming" Presented in Design and
Analysis of Algorithms (CMPT 705), Simon Fraser University, August 10, 2023.

[12] Tesseract-OCR. (2023, Aug). Tessdoc: Tesseract Documentation. [Online].
Available:https://github.com/tesseract-ocr/tessdoc

