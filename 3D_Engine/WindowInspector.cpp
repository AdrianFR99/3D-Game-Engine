#include "WindowInspector.h"
#include "Application.h"
#include "imgui_defines.h"

#include "mmgr/mmgr.h"


WindowInspector::WindowInspector(char*title) : WindowUI(title)
{


}

WindowInspector::~WindowInspector()
{
}

bool WindowInspector::Display() {

	if (active)
		//Config_Window();


	return true;
}

void WindowInspector::Inspector_Window() {

	
	/*Config_Window_App();
	Config_Window_Window();
	Config_Window_FileSystem();
	Config_Window_Input();
	Config_Window_Camera();
	Config_Window_Hardware();
	Config_Window_Buttons();*/



	ImGui::End();

		
}
//
//void WindowInspector::Transformation_show() {
//
//	if (ImGui::CollapsingHeader("Transformation"))
//	{
//		ImGui::Spacing();
//		ImGui::Spacing();
//
//		//Display transformation
//
//		ImGui::Text("Transformation matrix:");
//		ImGui::SameLine();
//		
//	//	Display_Transform(vector);
//
//		
//
//
//		//Memory
//
//		ImGui::Text("Memory Stats");
//
//		sMStats MemStats = m_getMemoryStatistics();
//		static int ToUpdate = 0;	//var which it is used as an interval of time to update the data in the vector and in the graph
//		static std::vector<float>memory(LOG_MEM_SIZE_PLOT); //Creating a vector to allocate the memory data as we did with the FPS and ms
//
//
//
//		if (ToUpdate > TO_MOVE_VEC_DATA) {
//
//			if (memory.size() == LOG_MEM_SIZE_PLOT) {
//
//				for (uint i = 0; i < LOG_MEM_SIZE_PLOT - 1; ++i)
//					memory[i] = memory[i + 1];
//
//				memory[LOG_MEM_SIZE_PLOT - 1] = (float)MemStats.totalReportedMemory;
//			}
//			else
//				memory.push_back((float)MemStats.totalReportedMemory);
//
//			ToUpdate = 0;
//
//		}
//
//		ImGui::PlotHistogram("##Memory", &memory[0], memory.size(), 0, "Memory Consumption", 0.0f, (float)MemStats.peakReportedMemory*1.75f, ImVec2(310, 100));
//
//		ImGui::Spacing();
//		ImGui::Spacing();
//
//		ImGui::Text("Total Reported Memory: %u", MemStats.totalReportedMemory);
//		ImGui::Text("Total Actual Memory: %u", MemStats.totalActualMemory);
//		ImGui::Text("Peak Reported Memory: %u", MemStats.peakReportedMemory);
//		ImGui::Text("Peak Actual Memory: %u", MemStats.peakActualMemory);
//		ImGui::Text("Accumulated Reported Memory: %u", MemStats.accumulatedReportedMemory);
//		ImGui::Text("Accumulated Actual Memory: %u", MemStats.accumulatedActualMemory);
//		ImGui::Text("Accumulated Alloc Unit Count: %u", MemStats.accumulatedAllocUnitCount);
//		ImGui::Text("Total Alloc Unit Count: %u", MemStats.totalAllocUnitCount);
//		ImGui::Text("Peak Alloc Unit Count: %u", MemStats.peakAllocUnitCount);
//
//
//
//		++ToUpdate;
//
//	}
//
//
//}