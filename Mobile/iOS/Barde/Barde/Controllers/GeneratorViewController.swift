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

class GeneratorViewController: UIViewController {
    static let sharedInstance = GeneratorViewController()
    
    // this one is from a midi file
    var midiPlayer: AVMIDIPlayer!
    
    @IBOutlet weak var errorLabel: UILabel!
    var playButton:UIButton?
    @IBOutlet weak var controlButton: UIButton!
    @IBOutlet weak var labelCurrentTime: UILabel!
    var timer = Timer()
    var intCounter: Int = 0
    
    @IBOutlet weak var labelFullTime: UILabel!
    var styleViewController: StyleViewController?
    
    override func viewDidLoad() {
        super.viewDidLoad()
    
        let btnImage = UIImage(named: "icon-play")
        controlButton.setImage(btnImage , for: UIControlState.normal)
        controlButton.addTarget(self, action: #selector(GeneratorViewController.playButtonTapped(_:)), for: .touchUpInside)
        labelCurrentTime.text = "00:00"
        labelFullTime.text = "00:00"
    }
    
    var isPlaying: Bool = false
    
    @objc func playButtonTapped(_ sender:UIButton)
    {
        print(isPlaying)
        if (isPlaying) {
            stopPlaying()
        } else {
            let isOk = GeneratorManager.sharedInstance.sendData(arr: [0x2, 0x0, 0x0, 0x0, 0x12, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])

            if (isOk) {
                startPlaying()
            }
        }
    }
    
    func startPlaying() {
        
        let btnImage = UIImage(named: "ic_stop")
        self.controlButton.setImage(btnImage , for: UIControlState.normal)
        
        timer = Timer.scheduledTimer(timeInterval: 1.0, target: self, selector: #selector(updateCountdown), userInfo: nil, repeats: true)
        
        setSessionPlayer()
        createAVMIDIPlayerFromMIDIFIle()
        
        self.midiPlayer?.play({ () -> Void in
            print("finished")
            self.midiPlayer?.currentPosition = 0
        })
        
        isPlaying = true
    }
    
    func stopPlaying() {
        
        stopMidiPlayer()
        isPlaying = false

        let btnImage = UIImage(named: "icon-play")
        controlButton.setImage(btnImage , for: UIControlState.normal)
        
        timer.invalidate()
        labelCurrentTime.text = "00:00"
        labelFullTime.text = "00:00"
        intCounter = 0
        GeneratorManager.sharedInstance.sendData(arr: [0x2, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0, 0x0D, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0])
    }
    
    func stopMidiPlayer() {
        if let player = self.midiPlayer {
            if player.isPlaying {
                player.stop()
            }
        }
    }
    
    @objc func updateCountdown() {
        if (isPlaying){
            intCounter += 1
            
            labelCurrentTime.text! = String(format: "%02d:%02d", (intCounter % 3600) / 60, (intCounter % 3600) % 60)
        }
        // print(">>>", self.midiPlayer?.duration.toHHMMSSString())
        labelFullTime.text = self.midiPlayer?.duration.toHHMMSSString()
        if (labelCurrentTime.text == labelFullTime.text)
        {
           stopPlaying()
        }
    }
    
    func setSessionPlayer() {
        let audioSession = AVAudioSession.sharedInstance()
        do {
            try audioSession.overrideOutputAudioPort(AVAudioSessionPortOverride.speaker)
            try audioSession.setCategory(AVAudioSessionCategoryPlayAndRecord, with: .mixWithOthers)
            try audioSession.setActive(true)
        } catch {
            print("couldn't set category \(error)")
        }
    }
    
    func createAVMIDIPlayerFromMIDIFIle() {
        let midiFileURL = CustomFileManager.sharedInstance.getFileUrl(file: "file.mid")
        
        guard let bankURL = Bundle.main.url(forResource: "GeneralUser GS MuseScore v1.442", withExtension: "sf2") else {
            fatalError("\"GeneralUser GS MuseScore v1.442.sf2\" file not found.")
        }

        do {
            print("\(midiFileURL.path)")
            let data = try Data(contentsOf: midiFileURL)
            //errorLabel.text = Array<UInt8>(data)
            print("DATA:", Array<UInt8>(data))
            try self.midiPlayer = AVMIDIPlayer(data: data, soundBankURL: bankURL)
            print("created midi player with sound bank url \(bankURL)")
            self.midiPlayer.prepareToPlay()
        } catch let error {
            Alert.showBasic(on: self, with: "Error generating music", message: "An error is occured. Please try again")
            stopPlaying()
            print("Error --- \(error.localizedDescription)")
        }

        self.midiPlayer?.prepareToPlay()
    }
}
