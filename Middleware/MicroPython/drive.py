from devices import motor
import time

class Drive:
    def __init__(self,motorLeft,motorRight,vmax,wheelDiameter,trackWidth):
      self.mLi = motorLeft
      self.mRe = motorRight
      self.faktorMM2Tics     = 1000.0/(3.1415*wheelDiameter)
      self.faktorWinkel2Diff = trackWidth*3.1415/360.0

      self.dLi = self.mLi.getPosition()
      self.dRe = self.mRe.getPosition()
      self.vmax = vmax
              
    def fahre( self,left, right ):
      self.mLi.setSpeed( 0 )
      self.mRe.setSpeed( 0 )
      time.wait( 10 )

      targetLi = self.mLi.getPosition() + left
      targetRe = self.mRe.getPosition() + right

      # Passe Geschwindigkeit der beiden Raeder so an,
      # dass diese gleichzeitig ihr Ziel erreichen
      dges  = 0.5*(abs(left) + abs(right))

      if dges == 0:
        return

      self.mLi.setPosition(  speed=self.vmax * left/dges,  position=targetLi )
      self.mRe.setPosition(  speed=self.vmax * right/dges, position=targetRe )

      time.wait( 10 )

      while(   abs( self.mLi.getPosition() - targetLi ) > 1  
            or abs( self.mRe.getPosition() - targetRe ) > 1 ):
        pass

      time.wait( 10 )
    
    def track( self,distance, angle ):
      li = distance + self.faktorWinkel2Diff*angle
      re = distance - self.faktorWinkel2Diff*angle  
      self.fahre( self.faktorMM2Tics*li, self.faktorMM2Tics*re )
        
    def speed( self,left, right ):
      self.mLi.setSpeed( self.faktorMM2Tics*left )
      self.mRe.setSpeed( self.faktorMM2Tics*right )

    def power( self,left, right ):
      self.mLi.setPower( self.faktorMM2Tics*left )
      self.mRe.setPower( self.faktorMM2Tics*right )

    def brake( self ):
      self.mLi.brake(  )
      self.mRe.brake(  )
      
    def distanceReset( self ):
      self.dLi = self.mLi.getPosition()
      self.dRe = self.mRe.getPosition()

    def distance( self ):
      li = self.mLi.getPosition()-self.dLi
      re = self.mRe.getPosition()-self.dRe
      return 0.5*(li + re)/self.faktorMM2Tics+0.5

    def angle( self ):
      li = self.mLi.getPosition()-self.dLi
      re = self.mRe.getPosition()-self.dRe
      return 0.5*(li - re)/(self.faktorMM2Tics*self.faktorWinkel2Diff)+0.5
