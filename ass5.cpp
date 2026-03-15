//////////////////////////////////ass5.cpp file////////////////////////////////
//-----------------------------------------------------------------------------
// Created by Micah Rice & Bruce Nguyen on 03/04/2021.
// 
// Driver/Tester demonstrating functions of threadedBST class 
// takes user input, constructs threadedBSTs, demonstrates copyconstructor
// and removes evens, displaying states of threadedBST
// uses << operator on threadedBST which uses iterator class
// to perform an inorder traversal of the threadedBST using threads
// to output the data fields of the entire threadedBST in a single line 


#include <cassert>
#include <iostream>
#include <string>

#include "threadedBST.h"

using namespace std;

//-----------------------------------------------------------------------------
// removeEvens()
// removes the nodes containing even numbers from a threadedBST
// PRE: threadedCopy exists as a threadedBST object
// POST: the threadedCopy threadedBST object
//       has no nodes with even number data fields, all being removed
void removeEvens(threadedBST &threadedCopy) {
  int i = 2;
  while (threadedCopy.remove(i)) {
    i += 2;
  }
}


//-----------------------------------------------------------------------------
// input()
// user input of any non-negative number including zero 
// returned as int n
// PRE: user has access to console, can input numbers
// POST: int n is returned as the user inputted non-negative number
int input() {
  int n;
  string prompt = "Please enter a non-zero positive integer: ";
  cout << prompt;
  cin >> n;
  while (n < 0) {
    cout << prompt;
    cin >> n;
  }
  return n;
}


//-----------------------------------------------------------------------------
// userDefinedTest()
// takes user input and creates threadedBSTs according to input n.
//       trees are then displayed, and destroyed, repeating until input is zero 
//       note: uses iterator class in the << operator of threadedBST
// PRE: user has access to console, can input numbers
// POST: threadedBSTs created according to input n
//       have been displayed to cout, repeated as many times
//       as it took till the user inputted a 0
void userDefinedTest() {
  cout << endl << endl;
  cout << "=====================================================" << endl;
  cout << "======Begin threadedBST Progam with User Input=======" << endl;
  cout << "=====================================================" << endl;
  string exitPrompt = "To exit, enter 0.";
  cout << exitPrompt << endl;
  int n = input();
  while (n > 0) {
    threadedBST threaded(n);
    assert(!threaded.isEmpty());
    threadedBST threadedCopy(threaded);
    //<< operator uses the iterator class
    cout << endl << "original threadedBST, N = " << n << endl;
    cout << threaded;
    cout << endl << "Copy of threadedBST, N = " << n << endl;
    cout << threadedCopy;
    removeEvens(threadedCopy);
    cout << endl
         << "Copy of threadedBST, N = " << n
         << ", with evens removed: " << endl;
    cout << threadedCopy;
    cout << endl
         << "original threadedBST, N = " << n << ", unaltered: " << endl;
    cout << threaded;
    cout << endl << endl << exitPrompt << endl;
    cout << endl << endl;
    n = input();
  }
}

//-----------------------------------------------------------------------------
// main()
// calls functions to test every case possible to get 100% code coverage
// for all of threadedBST and iterator class functions
// and calls userDefinedTest to created user defined threadedBSTs
// PRE: threadedBST exists as a data type, 
//      console is 80 characters wide or more
// POST: many threadedBSTs have been printed to cout, 
//       ascii art is displayed showing end of program
int main() {
  userDefinedTest();
  cout << endl;
  cout << "===================================================================="
          "==========="
       << endl;
  cout << "===================================================================="
          "==========="
       << endl;
  cout << "                                                                    "
          "     ,B:   "
       << endl;
  cout << "                                                                    "
          "    :@@    "
       << endl;
  cout << "                                                                    "
          "   :L@     "
       << endl;
  cout << "                                                                    "
          "  .i@2,:.  "
       << endl;
  cout << "                                                                    "
          "  :@@, 7r  "
       << endl;
  cout << "                                                          .         "
          " ,uBM;:i:  "
       << endl;
  cout << "                                                                    "
          ".rB@....   "
       << endl;
  cout << "                                                                    "
          "iG@i  .    "
       << endl;
  cout << "                                                     .             "
          ":L@5 .      "
       << endl;
  cout << "                      .             . .               ..         "
          ".,:@B,i,..    "
       << endl;
  cout << "                                    7k                ..      . "
          ".:,2@i,r..:,   "
       << endl;
  cout << "                      :iY2kUYi:.::,7vi         ..   .        ,: "
          ".:iBO ,:,.,    "
       << endl;
  cout << "                 irvFFvr:.. .:::L0XUv      .. ...:.        ..:. "
          "::O@: .:..     "
       << endl;
  cout << "              iP@G7,. . ..,...,,::.r@B@7  .ZL:5i .:        :ii, "
          ":r@X: .:.      "
       << endl;
  cout << "            ;@B5:  ..,,:...::.ii.Lu  UM@BFu07.:i::.     .. ,::  .@B "
          ":  .       "
       << endl;
  cout << "          iB@r    .:..:,: .,i:::. qY.iE@@B@r,:,..       .       1B: "
          "           "
       << endl;
  cout << "         @BS    .,.:  ,,:..::Y:i. rZv8B@BMB@v  :,.   .         iBO  "
          "           "
       << endl;
  cout << "       :MZ:  . ...,.. .,:,.:.1u.,:NjPS@O@BPB@M:   ,           .M@   "
          "           "
       << endl;
  cout << "  :,  ;u:.    .,... .. ::,.:.7ui111.UJB@B@8MB@BGL:.  ,.  . ., v@U:, "
          "::.  .  .  "
       << endl;
  cout << "  iLv77.     ....   .. ,. ..,JuNG;i5:rNB@BBOXB@BZEL. ,: .,   ,@B i: "
          "ii, .  ..  "
       << endl;
  cout << "    .:,      ,..... .. , ,,::v:5: M@ ::MB@M@NNB@r  ..:i. ... UB: "
          "i:.i::..      "
       << endl;
  cout << "     ..     .,. ... .,. .,:,:  , ,@@.: rPBE@@k@B@i ..:i     :BM  "
          ":7ii :..      "
       << endl;
  cout << "     :..    .: ...  .:..r..:, BU .Y@r@i:5Lvk@MB@LO...ii.    "
          "8@...:vv: ,i:.     "
       << endl;
  cout << "     ....    ,. .,  .,.:8.  71@.viiMB@8 :.i2@UEBYir.,,,    i@U "
          "::,,::..        "
       << endl;
  cout << "     . ..        :......B1 :B@,.2;:MB@0 ,L;FBv1@L .,,,..   @B "
          ".:,,..,.         "
       << endl;
  cout << "    .:..,     :P:., .,, @Y B@: .,,iMBO2qZM:vMLOM@   ,..   YBi "
          "::,,,..          "
       << endl;
  cout << "    ,, . . . .:i :.. ir O UO,rSJ.i7GBB8Gir i,PB8B@u;i.   .@@ :;7r:  "
          "           "
       << endl;
  cout << "      . .  .,r:  r YU:7 iYv.YB1:i1S5BB@B@kr1r5SJ rj:i.   5@: Uu:r.  "
          "           "
       << endl;
  cout << " ..  :... .,  U@v: :@i, ;:  . .XBBNS0@B@G1Bk@@F: :...   ,@F,:L5:    "
          "           "
       << endl;
  cout << "      .: .i...PM7.. YB  :,LSk8@@MMGukB@BZB@B@BY .:,     MB;u:,,     "
          "  .        "
       << endl;
  cout << "      .7  ,i:,:;7:   uY,7vGBBBOMOONj7UP2B@B@B@i. ,     :BEkr        "
          "        .. "
       << endl;
  cout << "       .  .,rLFUUi   ,r::JkSFSXXqqZ1ir7J@B@B@MrFi7.    B@ :         "
          "  .    ..  "
       << endl;
  cout << "           , :ju7.   :i;i77juUu51XPO8ZPBOBB@BJ;;X@j   .@            "
          "           "
       << endl;
  cout << "           v. ,.    . .iUkUJuJuuUUX2uuPSPB@B2   @BL7i M@S,      .   "
          "           "
       << endl;
  cout << "            Y. :L7     ..ruFuuuuJuvrv2kBB@Bv  ,u7.   7O:8@i   ,:.   "
          "           "
       << endl;
  cout << "             :   vO: . ....:7Y2U1uujuLJ8@Bj.:iY. 77  B  .1@U;,::.   "
          ".,. ....   "
       << endl;
  cout << "                  ,k:7 ,,::,.,:r7uu2U15GMu:;:, .Lr  Pi  .v0@Bj ..   "
          ".i  ,.     "
       << endl;
  cout << "                   v::U i:i::::::.  ::i;,      i   i0  .LL8Z@,  .   "
          ",:.  ..    "
       << endl;
  cout << "                 ...  vi ::::i,                   .0   viJU :   ..  "
          " ,.    .   "
       << endl;
  cout << "                  :: ,i,.,::i.       ,vj8B@BXi7Ji LJ  5Ji:7i   ,i.. "
          "vq         "
       << endl;
  cout << "              iU7rr::iii..:::::r     .,,iL:. YB@: BG ...vuri;: ..  "
          ".M@EvuZP5:  "
       << endl;
  cout << "           .vUE:.   iLui:,::i:.             r@M7 J@@..,.  "
          "vkJk7;v7rLLrLUuuFM@BO"
       << endl;
  cout << "      7@JiqOFi,... .iXj7ii::                Bkv ,@q,   "
          ".:irYvY7L5ZJi::       iB"
       << endl;
  cout << "     ;P7,.:::,:..  .irrii::     .           L   @i    .:7J7:.  .2EY "
          "          J"
       << endl;
  cout << "     U      .::...  rrL7i:.ui:ir:.,ii:.,5Jr.   XB   .:;7r7vL77:.   "
          ",.  ,..:.  2"
       << endl;
  cout << "     :        ,.... i:rLr:;iEB@G1L7i::rq@BBBi ,B. "
          "..,,:::,:i7vuL7i:., :j:,i. ,@"
       << endl;
  cout << "    ii          .::.:i.:;r  P@B@PLii;PB@@@G:  8@ ,.  .     "
          "..:iYYYj17iiL,,. 7B@"
       << endl;
  cout << "    .           ,,:..i.ir, .qB@SUuuvjOBM0:   :@:,, ..         "
          ".:iv11ZOGSi  7NBB"
       << endl;
  cout << "   .             ,,:     .  P@BN5X0OZ8L.     @Z..:u82j.          "
          ".;rLSNZ8Gi i2 "
       << endl;
  cout << "  ,:           .. .v:     ..,vN0PYJ7:       k@,,.:0227        ..    "
          ".,7YuF8BZZr"
       << endl;
  cout << "  .   ....     ..  27       ..       .:    iBv.:,:1Fr,         ..   "
          "    .iUGO@B"
       << endl;
  cout << ",,        .     .  i,..       . ,    :.   rBN ::. rO:               "
          "        :7S"
       << endl;
  cout << ",.              .  ...,ii.     ,k.       iJ@ ,,.  iML.              "
          ".      i   "
       << endl;
  cout << "                . ... 7Yiq7           .  .@:  :,..  MJ.          "
          ",ri.    .@Bv.L"
       << endl;
  cout << "               ...    .2Y1Mki           .BX :L5u,J7  F2i..     "
          ":77:. .:. 1B@. B"
       << endl;
  cout << "                ,.,.....irJuuFui        JB:vuY1v vFJ, :rvvYvv;i:. . "
          "  .: 1@j  @"
       << endl;
  cout << "                 .,,...  :ii,.i27. ,ii .BPiJYuYr JUuL,  .,::.       "
          "   7 LBF  q"
       << endl;
  cout << "           .       .. .:JL7,ri::vFPMZ. S@iLUUJ2i.YLii.  ,           "
          "   i..ii  ,"
       << endl;
  cout << "        ...      . .:vuMuXBM@@B@B@B@: i@Prvi7Yr, r:r7, . .          "
          "  .r :::. ."
       << endl;
  cout << "   .,,::.        i7L57: JB@BOP0GO5u07 UB:ir..rr:.Uuu2,....,     .  "
          ".. ,i  .::::"
       << endl;
  cout << ".:::,::,    vviiri::   ,v0B@B@Gv.. iB7Gv.:.. :1::FjUj, ...,.     .  "
          " . :.      "
       << endl;
  cout << ".         .Yu:,,..    qB@Y:Y@B@Mi,  :F7ii:::. i:JJYLi .....:   "
          ".......,..      "
       << endl;
  cout << " ..,,  ::..    ..  . :jGB@Ov.,.iuL .L:r@Fv7v,   :.     ... ..    . "
          "..,,       ."
       << endl;
  cout << ":::::::.........   . Eu i1Okv.   rrJ2:rM@O8BZBu;J: .L...... :.      "
          "...        "
       << endl;
  cout << "   .     ,,:....  ,..5S:   :7JL:  :7:.:vG@Piu@M@BM0@B  . ..,:.     "
          "..,:      .."
       << endl;
  cout << "  .   ..,,,      .i..:J5L  ::i1G7 .ir7uLL@@;JvLGMB@@7   ..,,,    "
          ".... :        "
       << endl;
  cout << "     ..,..             .7NL: .,:Uqrv5@qLu@PSU2YXN@OZY7r:.:,,i::.    "
          "           "
       << endl;
  cout << "    ,.       .r7. :i:   ivuLi.   .:i5XuLFFYUFJZB@OXr.:B5,,::ii:  .  "
          "           "
       << endl;
  cout << "   ..  .ii::.:ir .kP:.rv.:urvL  7. 72vvuqP5qOXBMF@Pri:iFS:::,ri ..  "
          ",,         "
       << endl;
  cout << "  .. .rr:       .iF:.:r:,iu,i .    MEkSO@B@BPOEFM1M2iui:r:::r17r.   "
          ",         ."
       << endl;
  cout << " ...,i.        :iri:i:,:::.7 .   .iSB@BESBBNi@MEOG2v7vir:i:iFB:i. "
          "..       . . "
       << endl;
  cout << ",.           .i::.,.::r..;u. .   NZ SB@OYO7vE1BBEB2rrrririrLPM  ri. "
          "      .... "
       << endl;
  cout << "     . .    .ri,  7r.:v,.77 :.Y7v@PBFYXSrrqMMq2OEFv7rr;rivU128  Zi  "
          "       ,.. "
       << endl;
  cout << "  .  .. . .iri,.  ;7,.,..: : :uvSEP5BME2YUX1SuuYLr;rrr7ru21u1P. 70  "
          "       ...:"
       << endl;
  cout << ". .. .. .:i:,,..   ::,.,,.:r.::111uuLU2uU2juJuu1uv7v7YjFU1u2ukY  7L "
          "      .,.:i"
       << endl;
  cout << "... . ..:::,,.,..,: ..,.ir:..:u22uuuUUUjUU11S1UYv7LJ51FU121uUX@   "
          ":i:   . ..,i1"
       << endl;
  cout << ".,    .:,,,:::.,::,. ..,.7, :uUuu12k5S2F1FUj77rL2qZNFkU1uUJ1P@r  .  "
          "iu;  ..:Yv:"
       << endl;
  cout << "...  ...,.,,,..r:.... . .,..5ZqXqXNX1juYvrr:710ZGPXUY7vu2uS0BY  .   "
          " :uUi:7ui  "
       << endl;
  cout << ",. . ,:,...... 7: ...... . ,JU1k2UYvr7rr7u58GEF2Lv7LLUFkF0qZG    "
          "...   rYLr:.:,"
       << endl;
  cout << ".,...:7:.,:... iv:... . .  .77Y7rr77vL1kZZq2Livj2Z@S11XXEq0ZM:. "
          "....      ri,,."
       << endl;
  cout << ",. . ,i,.,:,  .77i..    .. ..:r7vju5k0qkuvLuFPEOZMGPFqqE0GEGOL..:: "
          ",, ,i,ii:,  "
       << endl;
  cout << ",..  .:...... rr:.. .i.   :vYJ5jYLJLL77LNkMq0Fq5S25FPXNqE0Z0Oj "
          ".:,.:r.:ii:i:, :"
       << endl;
  cout << ".,   ,:. ... ir:... :Yvr:::irv77r7vjSqBkXPUSXP5PkXSPkqNE0ZEZ0M: "
          "::.i7,:Y:,7r:::"
       << endl;
  cout << ".   .., ....ii:,... . ,:;LXULvu0O8@GGPXU2u21Pq0qE00qE0ZEGEG00Mr "
          "...::,:::,;::::"
       << endl;
  cout << "   .....,,.,i:,,..      .iL1FqEZN0PPkN15FXS1YvL5kNEGGOG8Z8ZGF2X. "
          ".,,.,.,,:,::::"
       << endl;
  cout << "  . ...,:,,::,,.         .:.::iirr7vYLJYLvu1XSS5UrrLjuFSPPSLi:F: "
          ".,,,.,,,,:::,,"
       << endl;
  cout << " ...,:.::,::..                     . "
          "...;JvvvJ1q0ZX1v7iiiriri;u0....,:..,:.,::,"
       << endl;
  cout << "..:i7i,::::,...         ...............i2jLvv7ri7v2qGE0FUYJvrv5ku:i "
          "ir: 77,:v77"
       << endl;
  cout << "===================================================================="
          "==========="
       << endl;
  cout << "===================================================================="
          "==========="
       << endl;
  cout << "============================DONE! HAVE A GOOD "
          "SPRING!=========================="
       << endl;
  cout << "===================================================================="
          "==========="
       << endl;
  return 0;
}
