#undef IMGUI_DEFINE_PLACEMENT_NEW
#define IMGUI_DEFINE_PLACEMENT_NEW
#undef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#define NOMINMAX
#include "../Backend/Algoritm.h"
#include "Meniu.h"
#include <d3d9.h>
#include <Windows.h>
#include "Fontawesome.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_internal.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <limits>
#include "../ImGui/ImPlot/implot.h"
#include "../Backend/math.h"

void Meniu::Afisare(Renderer* renderer) {
	/*ImGui::SetNextWindowSize(ImVec2(static_cast<float>(renderer->lungime), static_cast<float>(renderer->inaltime))); // Marimea ferestrei
	ImGui::SetNextWindowPos(ImVec2(0, 0)); // Pozitia ferestrei

	ImGui::Begin("nice", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::BeginColumns("mainmenu", 2, ImGuiOldColumnFlags_NoBorder);
	if (ImGui::Button("Sortviwer")) {
		//SetareStare(1); E mai ment
		stare = 1;
	}
	ImGui::NextColumn();
	if (ImGui::Button("Pathfinder")) {
		//SetareStare(2);  E mai lent
		stare = 2;
	}
	ImGui::EndColumns();
	ImGui::End();*/
	Sortare(renderer);
}
// 82	82	140
// 251,255,241

void Meniu::Sortare(Renderer* renderer) {
	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImGui::ColorConvertU32ToFloat4(IM_COL32(82, 82, 140, 255)));
	ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertU32ToFloat4(IM_COL32(251, 255, 241,255)));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGui::ColorConvertU32ToFloat4(IM_COL32(82	,82,140,255))); // culoarea ferestrei
	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(renderer->lungime), static_cast<float>(renderer->inaltime))); // Marimea ferestrei
	ImGui::SetNextWindowPos(ImVec2(0, 0)); // Pozitia ferestrei
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // fara padding
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0); // fereastra patratica
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	
	if(ImGui::Begin("Sortare", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar)) {
		if (ImGui::BeginChild("top-page-algorithm", ImVec2(1280, 80), true)) {

			ImGui::Dummy(ImVec2(426.6f / 4, 80));

			ImGui::SameLine(0, 0);

			ImGui::Dummy(ImVec2(426.6f - 426.6f / 4, 80));

			ImGui::SameLine(0, 0);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			
			ImGui::Button("Vizualizare sortare", ImVec2(426.6f, 80));
			ImGui::SameLine(0, 0);

			ImGui::PopStyleColor(3);

			ImGui::Dummy(ImVec2(426.6f - 426.6f / 4,80));
			ImGui::SameLine(0, 0);
			ImGui::Dummy(ImVec2(426.6f / 4, 80));

		} ImGui::EndChild();
		ImGui::PushFont(GLOBAL::render->fontnormal);
		ImVec2 size = ImGui::GetContentRegionAvail();
		if (ImGui::BeginChild("jos",ImVec2(size.x,size.y - 60),false)) {
			ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetCursorPos(), ImGui::GetCursorPos() + ImVec2(size.x,size.y + 20),IM_COL32(180,197,228,255));
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] - ImVec4(0,0,0,0.5));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] - ImVec4(0, 0, 0, 0.5));
			if (!std::is_sorted(GLOBAL::sortare->valori.begin(),GLOBAL::sortare->valori.end()) && GLOBAL::sortare->sortare) {
				timpf = static_cast<float>(GetTickCount64());
				durata = (timpf - timpi) / 1000;
			}
			if (ImGui::Button("Setare aleatorie",ImVec2(size.x / 3,80))) {
				if (!GLOBAL::sortare->sortare) {
					GLOBAL::sortare->wait = true;
					GLOBAL::sortare->valori.resize(100);
					int max = 0;
					for (int i = 0; i < 100; i++) {
						int random = MATH::RandomNumber(10, 50000);
						GLOBAL::sortare->valori[i] = random;
						if (random > max) {
							max = random;
						}
					}
					distributie.resize(max + 1);
					std::fill(distributie.begin(), distributie.end(), 0);

					for (unsigned int i = 0; i < GLOBAL::sortare->valori.size(); i++) {
						distributie[GLOBAL::sortare->valori[i]]++;
					}
					durata = 0;
					GLOBAL::sortare->wait = false;
				}
			}
			if (ImGui::IsItemHovered()) {
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			} ImGui::SameLine(0, 0);
			if (ImGui::Button("Sorteaza", ImVec2(size.x / 3, 80))) {
				timpi = static_cast<float>(GetTickCount64());
				GLOBAL::sortare->sortare = true;
			} 
			if (ImGui::IsItemHovered()) {
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			} ImGui::SameLine(0, 0);
			if (ImGui::Button(ICON_FA_BARS, ImVec2(size.x / 3, 80))) {
				ImGui::OpenPopup("Menu-popup");
			}
			if (ImGui::IsPopupOpen("Menu-popup")) {
		
				if(ImGui::BeginPopup("Menu-popup")) {
					ImGui::Dummy(ImVec2(250, 20));
					ImGui::SetNextItemWidth(250);
					ImGui::Combo("##algsort", &GLOBAL::sortare->sortmode, "Bubble Sort\0QuickSort\0Merge Sort\0Insertion sort\0HeapSort\0");
					ImGui::Dummy(ImVec2(250, 20));
					ImGui::Text("Viteza animatie:");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderInt("##nice", &GLOBAL::sortare->viteza, 0, 500, "%dms");
					/*if (ImGui::Button("Sortare instanta", ImVec2(500, 30))) {
						GLOBAL::sortare->sortare = false;
						std::sort(GLOBAL::sortare->valori.begin(), GLOBAL::sortare->valori.end());
					} */
					/*if (ImGui::CollapsingHeader("Statistici", ImGuiTreeNodeFlags_Framed)) {
						ImGui::TextWrapped("Grafic cu numerele");
						static bool once;
						static std::vector<int> da;
						if (!once) {
							for (int i = 0; i < 1000; i++) {
								da.push_back(i);
							}
						}
						if (!GLOBAL::sortare->valori.empty()) {
							
						}
					} */
				} ImGui::EndPopup();
					
			}
			if (ImGui::IsItemHovered()) {
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			}
			ImGui::PopStyleColor(3);
			ImGui::Dummy(ImVec2(10, 30));
			ImGui::Text(" Timp petrecut sortand: %.2f",durata);
			int start = 0;
			for (unsigned int i = 0; i < GLOBAL::sortare->valori.size(); i++) {
				ImVec2 beg = ImVec2(static_cast<float>(start),ImGui::GetWindowSize().y + 60.f - GLOBAL::sortare->valori[i] / 100.f);
				ImVec2 end = beg + ImVec2(12.5f, GLOBAL::sortare->valori[i] + ImGui::GetWindowSize().y + 60.f);
				ImVec4 color;
				if (i == GLOBAL::sortare->next) color = ImVec4(0.90f, 0.90f, 0.f, 1.f);
				else if (i == GLOBAL::sortare->current) color = ImVec4(0.40f, 0.90f, 1.00f, 1.f);
				else color = ImVec4(1.f, 1.f, 1.f, 1.f);
				ImGui::GetWindowDrawList()->AddRectFilled(beg,end,ImGui::ColorConvertFloat4ToU32(color), 0);
				ImGui::GetWindowDrawList()->AddRect(beg, end, IM_COL32(0, 0, 0, 255));
				start += 12;
			}		
		}; ImGui::EndChild();
		ImGui::PopFont();
	} ImGui::End();
	ImGui::PopStyleVar(3);
	ImGui::PopStyleColor(3);
}

int Meniu::IaStare() {
	return meniu->stare;
}

void Meniu::SetareStare(const int& st) {
	meniu->stare = st;
}

Meniu* meniu = new Meniu();