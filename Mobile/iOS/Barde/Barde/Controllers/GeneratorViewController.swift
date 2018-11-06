//
//  GeneratorViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 26/05/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit
import AVKit
import SwiftSpinner

class GeneratorViewController: UIViewController {
    
    static let sharedInstance = GeneratorViewController()
    
    // this one is from a midi file
    var midiPlayer: AVMIDIPlayer!
    
    @IBOutlet weak var navSlider: UISlider!
    @IBOutlet weak var errorLabel: UILabel!
    var playButton:UIButton?
    @IBOutlet weak var controlButton: UIButton!
    @IBOutlet weak var labelCurrentTime: UILabel!
    var timer = Timer()
    var intCounter: Int = 0
    
    @IBOutlet weak var labelFullTime: UILabel!
    var styleViewController: StyleViewController?
    
    var sv: UIView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        configureView()
        
    }
    
    override func viewDidAppear(_ animated: Bool) {
        setSessionPlayer()
    }
    
    func configureView() {
        navSlider.value = 0.0
        navSlider.setThumbImage(UIImage(named: "ic_circle"), for: UIControl.State.normal)
        let btnImage = UIImage(named: "icon-play")
        controlButton.setImage(btnImage , for: UIControl.State.normal)
        controlButton.addTarget(self, action: #selector(GeneratorViewController.playButtonTapped(_:)), for: .touchUpInside)
        labelCurrentTime.text = "00:00"
        labelFullTime.text = "00:00"
    }
    
    var isPlaying: Bool = false
    
    @objc func playButtonTapped(_ sender:UIButton)
    {

        self.showSpinner { error in
            if error != nil {
                print("Oops! Something went wrong...")
            } else {
                print("It has finished show spinner")
                
                if (!self.isPlaying) {
                    GeneratorManager.sharedInstance.sendData(arr: [0x2, 0x0, 0x0, 0x0, 0x12, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])
                    
                    sleep(1)
                    
                    self.playMidi { error in
                        if error != nil {
                            print("Oops! Something went wrong...")
                        } else {
                            print("It has finished init")
                            
                            self.waitStopPlayerMidi { error in
                                if error != nil {
                                    print("Oops! Something went wrong...")
                                } else {
                                    print("It has finished")
                                    self.startMidiPlayer()
                                }
                            }
                        }
                    }
                } else {
                    self.stopMidi { error in
                        if error != nil {
                            print("Oops! Something went wrong...")
                        } else {
                            self.stopMidiPlayer()
                            
                        }
                    }
                    
                }
                
            }
        }
        
        
    }

    @IBAction func stopButtonTapped(_ sender: Any) {
        stopMidiPlayer()
    }
    
    private func stopMidiPlayer() {
        if let player = self.midiPlayer {
            if player.isPlaying {
                isPlaying = false
                player.stop()
            }
        }
        
        DispatchQueue.main.async {

            let btnImage = UIImage(named: "icon-play")
            self.controlButton.setImage(btnImage , for: UIControl.State.normal)
            
            // timer.invalidate()
            self.labelCurrentTime.text = "00:00"
            self.labelFullTime.text = "00:00"
            // intCounter = 0
            
        }
        SwiftSpinner.hide()


    }
    
    private func startMidiPlayer() {
        self.isPlaying = true
        let btnImage = UIImage(named: "ic_stop")
        self.controlButton.setImage(btnImage , for: UIControl.State.normal)
        
        self.midiPlayer?.play({ () -> Void in
            print("finished")
            self.isPlaying = false
            
            DispatchQueue.main.async {
                
         
                let btnImage = UIImage(named: "icon-play")
                self.controlButton.setImage(btnImage , for: UIControl.State.normal)
                
            }
            self.midiPlayer?.currentPosition = 0
        })
        
        SwiftSpinner.hide()
    }
    
    func waitStopPlayerMidi(completion: @escaping (Error?) -> Void) {
        if (isPlaying) {
            self.stopMidiPlayer()
        }
        completion(nil)
    }
   
    func playMidi(completion: @escaping (Error?) -> Void) {
        createAVMIDIPlayerFromMIDIFIle()

        completion(nil)
    }
    
    func showSpinner(completion: @escaping (Error?) -> Void) {
        SwiftSpinner.show(NSLocalizedString("Loading.text", comment: ""))
        print("showSpinner")
        completion(nil)
    }
    
    
    func stopMidi(completion: @escaping (Error?) -> Void) {
        GeneratorManager.sharedInstance.sendData(arr: [0x2, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])

        completion(nil)
    }
    
    
//
//    func startPlaying() {
//
//        // timer = Timer.scheduledTimer(timeInterval: 1.0, target: self, selector: #selector(updateCountdown), userInfo: nil, repeats: true)f
//
//
//        initMidiPlayer { error in
//            if let error = error {
//                print("Oops! Something went wrong...")
//            } else {
//                print("It has finished")
//
//            }
//        }
//
//        let btnImage = UIImage(named: "ic_stop")
//        self.controlButton.setImage(btnImage , for: UIControl.State.normal)
//        self.midiPlayer?.play({ () -> Void in
//            print("finished")
//
//            DispatchQueue.main.async {
//                self.stopPlaying()
//            }
//
//            self.midiPlayer?.currentPosition = 0
//        })
//
//        isPlaying = true
//    }
    
//    func stopPlaying() {
//
//        stopMidiPlayer()
//        isPlaying = false
//
//        let btnImage = UIImage(named: "icon-play")
//        controlButton.setImage(btnImage , for: UIControl.State.normal)
//
//        // timer.invalidate()
//        labelCurrentTime.text = "00:00"
//        labelFullTime.text = "00:00"
//        // intCounter = 0
//        GeneratorManager.sharedInstance.sendData(arr: [0x2, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])
//
//        CustomFileManager.sharedInstance.deleteFile(file: CustomFileManager.sharedInstance.getFileUrl(file: "file.mid"))
//        CustomFileManager.sharedInstance.createFile(file: CustomFileManager.sharedInstance.getFileUrl(file: "file.mid"))
//
//    }
    
//    func stopMidiPlayer() {
//        if let player = self.midiPlayer {
//            if player.isPlaying {
//                player.stop()
//                self.stopPlaying()
//            }
//        }
//    }
    
//    @objc func updateCountdown() {
//        if (isPlaying){
//            intCounter += 1
//
//            labelCurrentTime.text! = String(format: "%02d:%02d", (intCounter % 3600) / 60, (intCounter % 3600) % 60)
//        }
//        // print(">>>", self.midiPlayer?.duration.toHHMMSSString())
//        labelFullTime.text = self.midiPlayer?.duration.toHHMMSSString()
//        if (labelCurrentTime.text == labelFullTime.text)
//        {
//           stopPlaying()
//        }
//    }
    
    func setSessionPlayer() {
        let audioSession = AVAudioSession.sharedInstance()
        do {
            let test = try audioSession.setCategory(AVAudioSession.Category.playback, mode: .default, options: [.mixWithOthers])
            print("tessss", test)
            try audioSession.setActive(true, options: .notifyOthersOnDeactivation)
        } catch {
            print("couldn't set category \(error)")
        }
    }
    
    func createAVMIDIPlayerFromMIDIFIle() {
        let midiFileURL = CustomFileManager.sharedInstance.getFileUrl(file: "file.mid")

        print("\(midiFileURL.path)")
        
        guard let bankURL = Bundle.main.url(forResource: "GeneralUser GS MuseScore v1.442", withExtension: "sf2") else {
            fatalError("\"GeneralUser GS MuseScore v1.442.sf2\" file not found.")
        }
        
        
        do {
            let midiData = try Data(contentsOf: midiFileURL)
            print("DATA:", Array<UInt8>(midiData))
            try self.midiPlayer = AVMIDIPlayer(data: midiData as Data, soundBankURL: bankURL)
            if (self.midiPlayer === nil) {
                createAVMIDIPlayerFromMIDIFIle()
            }
            print("created midi player with sound bank url \(bankURL)")
        } catch let error {
            print("Error \(error)")
        }
        
        if (self.midiPlayer !== nil) {
            self.midiPlayer?.prepareToPlay()
            setupSlider()
        }


        
    }
    
    var sliderTimer: Timer?
    
    func setupSlider() {
        sliderTimer = Timer.scheduledTimer(timeInterval: 0.1,
                                           target: self,
                                           selector: #selector(updateSlider),
                                           userInfo: nil,
                                           repeats: true)
        
        if let duration = midiPlayer?.duration {
            navSlider.maximumValue = Float(duration)
            navSlider.value = 0.0
            print("duration \(duration)")
        }
        navSlider.addTarget(self, action: #selector(sliderChanged(sender:)), for: .valueChanged)
    }
    
    @objc func updateSlider() {
        if let player = self.midiPlayer {
            navSlider.value = Float(player.currentPosition)
            labelCurrentTime.text = player.currentPosition.toHHMMSSString()
            labelFullTime.text = player.duration.toHHMMSSString()
        }
    }
    
    
    @IBAction func sliderChanged(sender: UISlider) {
        sliderTimer?.invalidate()
        
//        if let player = self.midiPlayer {
//            player.stop()
//            player.currentPosition = TimeInterval(sender.value)
//            player.prepareToPlay()
//            setupSlider()
//            let btnImage = UIImage(named: "ic_stop")
//            self.controlButton.setImage(btnImage , for: UIControl.State.normal)
//            player.play({ () -> Void in
//
//                DispatchQueue.main.async {
//                    self.stopPlaying()
//                }
//
//            })
//
//            isPlaying = true
//        }
    }
}

// Helper function inserted by Swift 4.2 migrator.
fileprivate func convertFromAVAudioSessionCategory(_ input: AVAudioSession.Category) -> String {
	return input.rawValue
}
