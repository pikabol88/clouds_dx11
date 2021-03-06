#include "pch.h"
#include "SettingsController.h"
#include "Engine\Application\Time.h"

float SettingsController::turbidity = 2.0f;
float SettingsController::time = 0.0f;
std::string SettingsController::fpsStr = "";

void SettingsController::ImGuiNewFrame() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void SettingsController::ImGuiInit(const HWND hwnd, const Renderer renderer) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(renderer.getDevice(), renderer.getDeviceContext());
	ImGui::StyleColorsDark();
}

void SettingsController::DispalyFPSMonitor() {
	ImGui::Begin("FPS Monitor");

	if (Time::hasOneSecondPassed()) {
		int fps = Time::getFramesPerSecond();
		fpsStr = "FPS: " + std::to_string(fps) + " (" + std::to_string(1000.0f / fps) + " ms)";
	}

	ImGui::Text(fpsStr.c_str());
}

void SettingsController::DisplayTurbiditySlider() {
	ImGui::SliderFloat("Turbidity", &SettingsController::turbidity, 0.5f, 5.0f);
}

void SettingsController::DisplayTimeSlider() {
	ImGui::SliderFloat("Time", &SettingsController::time, 0.0f, 3.0f);
}

void SettingsController::ImGuiEndFrame() {
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
