@echo "�����error C2664: 'RtlStringFromGUID', ���޸� ControlGuid Ϊ *ControlGuid"

..\tools\tracing\tracewpp.exe -cfgdir:..\..\import\3rdparty\ntddk\wppconfig\rev1 -odir:.\ main.cpp kndisfirewall.cpp protocol.cpp miniport.cpp kipfilter.cpp karpfilter.cpp kadvipfilter.cpp -km -func:KAntiarpDebugPrint(LEVEL,FLAGS,MSG,...) -scan:.\..\..\import\kpfw\kwpptrace.h -ext:.cpp.CPP.h.H